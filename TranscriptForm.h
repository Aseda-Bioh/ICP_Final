#pragma once

namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    public ref class TranscriptForm : public System::Windows::Forms::Form
    {
    public:
        TranscriptForm(String^ studentID)
        {
            InitializeComponent();
            this->studentID = studentID;
            LoadTranscript();
        }

    protected:
        ~TranscriptForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        String^ studentID;
        System::Windows::Forms::DataGridView^ dgvTranscript;
        System::Windows::Forms::Label^ lblStudentInfo;
        System::Windows::Forms::Button^ btnPrint;
        System::Windows::Forms::Panel^ pnlTranscript;
        System::ComponentModel::Container^ components;
        System::Drawing::Printing::PrintDocument^ printDocument;
        System::Windows::Forms::PrintDialog^ printDialog;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->dgvTranscript = gcnew System::Windows::Forms::DataGridView();
            this->lblStudentInfo = gcnew System::Windows::Forms::Label();
            this->btnPrint = gcnew System::Windows::Forms::Button();
            this->pnlTranscript = gcnew System::Windows::Forms::Panel();

            // Panel configuration
            this->pnlTranscript->SuspendLayout();
            this->pnlTranscript->Controls->Add(this->dgvTranscript);
            this->pnlTranscript->Controls->Add(this->lblStudentInfo);
            this->pnlTranscript->Location = System::Drawing::Point(10, 10);
            this->pnlTranscript->Size = System::Drawing::Size(780, 500);  // Explicit size
            this->pnlTranscript->ResumeLayout();

            //DatagridView Configuration
            this->dgvTranscript->AllowUserToAddRows = false;
            this->dgvTranscript->AllowUserToDeleteRows = false;
            this->dgvTranscript->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvTranscript->Location = System::Drawing::Point(0, 100);
            this->dgvTranscript->Size = System::Drawing::Size(760, 380);
            this->dgvTranscript->ReadOnly = true;
            this->dgvTranscript->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
            this->dgvTranscript->RowHeadersVisible = false;
            this->dgvTranscript->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
            this->dgvTranscript->Anchor = static_cast<System::Windows::Forms::AnchorStyles>
                (System::Windows::Forms::AnchorStyles::Top |
                    System::Windows::Forms::AnchorStyles::Bottom |
                    System::Windows::Forms::AnchorStyles::Left |
                    System::Windows::Forms::AnchorStyles::Right);

            // Student Info Label
            this->lblStudentInfo->AutoSize = true;
            this->lblStudentInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
            this->lblStudentInfo->Location = System::Drawing::Point(10, 20);

            // Print Button
            this->btnPrint->Text = L"Print Transcript";
            this->btnPrint->Location = System::Drawing::Point(650, 520);
            this->btnPrint->Size = System::Drawing::Size(120, 30);
            this->btnPrint->Click += gcnew System::EventHandler(this, &TranscriptForm::btnPrint_Click);

            // Form configuration
            this->Controls->Add(this->pnlTranscript);
            this->Controls->Add(this->btnPrint);
            this->Text = L"Student Transcript";
            this->Size = System::Drawing::Size(800, 600);
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;

            this->printDocument = gcnew System::Drawing::Printing::PrintDocument();
            this->printDialog = gcnew System::Windows::Forms::PrintDialog();

            this->printDialog->Document = this->printDocument;
            this->printDocument->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &TranscriptForm::PrintDocument_PrintPage);
        }

        void LoadTranscript()
        {
            try {
                String^ connString = "Server=localhost;Database=university_system;Uid=root;Pwd=;";
                MessageBox::Show("Connecting to database...");
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                // Get student information
                String^ studentQuery = "SELECT s.studentID, s.programCode, CONCAT(u.firstName, ' ', u.lastName) as fullName, "
                    "s.batch FROM student s JOIN user u ON s.userID = u.userID WHERE s.studentID = @studentID";
                MySqlCommand^ studentCmd = gcnew MySqlCommand(studentQuery, conn);
                studentCmd->Parameters->AddWithValue("@studentID", studentID);
                MySqlDataReader^ studentReader = studentCmd->ExecuteReader();

                if (studentReader->Read()) {
                    String^ studentInfo = String::Format("Student ID: {0}\nName: {1}\nProgram: {2}\nBatch: {3}",
                        studentReader["studentID"]->ToString(),
                        studentReader["fullName"]->ToString(),
                        studentReader["programCode"]->ToString(),
                        studentReader["batch"]->ToString());
                    lblStudentInfo->Text = studentInfo;
                    MessageBox::Show("Student info loaded: " + studentInfo);
                }
                else {
                    MessageBox::Show("No student found with ID: " + studentID);
                }
                studentReader->Close();

                // Get transcript data using the student_grades view
                String^ query = "SELECT termCode, courseCode, courseName, credits, grade, gradePoint "
                    "FROM student_grades WHERE studentID = @studentID ORDER BY termCode, courseCode";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@studentID", studentID);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);

                // Calculate GPA
                double totalPoints = 0;
                int totalCredits = 0;
                for each (DataRow ^ row in dt->Rows) {
                    if (row["gradePoint"] != DBNull::Value && row["credits"] != DBNull::Value) {
                        totalPoints += Convert::ToDouble(row["gradePoint"]) * Convert::ToInt32(row["credits"]);
                        totalCredits += Convert::ToInt32(row["credits"]);
                    }
                }

                double gpa = totalCredits > 0 ? totalPoints / totalCredits : 0;

                // Add GPA information to student info label
                lblStudentInfo->Text += String::Format("\nCumulative GPA: {0:F2}", gpa);

                dgvTranscript->DataSource = dt;
                conn->Close();

                MessageBox::Show("Data loaded. Row count: " + dt->Rows->Count.ToString());
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading transcript: " + ex->Message + "\nStack trace: " + ex->StackTrace);
            }
        }

        void btnPrint_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try {
                if (this->printDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
                {
                    this->printDocument->Print();
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error printing: " + ex->Message, "Print Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void PrintDocument_PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e)
        {
            try {
                // Get the graphics object
                System::Drawing::Graphics^ g = e->Graphics;

                // Define fonts
                System::Drawing::Font^ headerFont = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
                System::Drawing::Font^ regularFont = gcnew System::Drawing::Font("Arial", 10);

                // Starting position
                int yPos = 50;
                int xPos = 50;

                // Print header
                g->DrawString("ACADEMIC TRANSCRIPT", headerFont, System::Drawing::Brushes::Black,
                    xPos, yPos);
                yPos += 30;

                // Print student info
                g->DrawString(this->lblStudentInfo->Text, regularFont, System::Drawing::Brushes::Black,
                    xPos, yPos);
                yPos += 100;

                // Print column headers
                String^ headerText = String::Format("{0,-15} {1,-10} {2,-40} {3,-10} {4,-10}",
                    "Term", "Code", "Course Name", "Credits", "Grade");
                g->DrawString(headerText, headerFont, System::Drawing::Brushes::Black, xPos, yPos);
                yPos += 30;

                // Get the data source
                DataTable^ dt = safe_cast<DataTable^>(dgvTranscript->DataSource);

                // Print each row
                for each (DataRow ^ row in dt->Rows)
                {
                    String^ lineText = String::Format("{0,-15} {1,-10} {2,-40} {3,-10} {4,-10}",
                        row["termCode"]->ToString(),
                        row["courseCode"]->ToString(),
                        row["courseName"]->ToString(),
                        row["credits"]->ToString(),
                        row["grade"]->ToString());

                    g->DrawString(lineText, regularFont, System::Drawing::Brushes::Black, xPos, yPos);
                    yPos += 20;

                    // Check if we need a new page
                    if (yPos > e->MarginBounds.Bottom - 50)
                    {
                        e->HasMorePages = true;
                        return;
                    }
                }

                // No more pages needed
                e->HasMorePages = false;

                // Clean up
                delete headerFont;
                delete regularFont;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error during printing: " + ex->Message, "Print Error",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    };
}