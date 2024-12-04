#pragma once
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace MySql::Data::MySqlClient;

    public ref class StudentGradesForm : public System::Windows::Forms::Form
    {
    private:
        String^ studentID;
        MySqlConnection^ sqlConnection;
        System::Windows::Forms::DataGridView^ dgvGrades;
        System::Windows::Forms::ComboBox^ cmbTerm;
        System::Windows::Forms::Label^ lblGPA;
        System::Windows::Forms::GroupBox^ grpGrades;
        System::ComponentModel::Container^ components;

    public:
        StudentGradesForm(String^ studentID)
        {
            InitializeComponent();
            this->studentID = studentID;
            ConfigureDatabase();
            LoadTerms();
            LoadGrades();
        }

    protected:
        ~StudentGradesForm()
        {
            if (components) {
                delete components;
            }
            if (sqlConnection) {
                sqlConnection->Close();
                delete sqlConnection;
            }
        }

    private:
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // Form settings
            this->Text = L"My Grades";
            this->Size = System::Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Term Selector
            this->cmbTerm = gcnew ComboBox();
            this->cmbTerm->Location = System::Drawing::Point(20, 20);
            this->cmbTerm->Size = System::Drawing::Size(200, 25);
            this->cmbTerm->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbTerm->SelectedIndexChanged += gcnew EventHandler(this, &StudentGradesForm::cmbTerm_SelectedIndexChanged);

            // Grades DataGridView
            this->dgvGrades = gcnew DataGridView();
            this->dgvGrades->Location = System::Drawing::Point(20, 60);
            this->dgvGrades->Size = System::Drawing::Size(740, 400);
            this->dgvGrades->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvGrades->AllowUserToAddRows = false;
            this->dgvGrades->AllowUserToDeleteRows = false;
            this->dgvGrades->ReadOnly = true;
            this->dgvGrades->MultiSelect = false;
            this->dgvGrades->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvGrades->RowHeadersVisible = false;

            // GPA Label
            this->lblGPA = gcnew Label();
            this->lblGPA->Location = System::Drawing::Point(20, 480);
            this->lblGPA->Size = System::Drawing::Size(740, 25);
            this->lblGPA->Font = gcnew System::Drawing::Font(L"Segoe UI", 10, System::Drawing::FontStyle::Bold);
            this->lblGPA->TextAlign = System::Drawing::ContentAlignment::MiddleRight;

            // Add controls to form
            this->Controls->Add(this->cmbTerm);
            this->Controls->Add(this->dgvGrades);
            this->Controls->Add(this->lblGPA);
        }

        void ConfigureDatabase(void)
        {
            String^ connectString = "server=localhost;port=3306;database=university_system;uid=aseda;password=FatherAbraham2";
            try {
                sqlConnection = gcnew MySqlConnection(connectString);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Database configuration error: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void LoadTerms(void)
        {
            try {
                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                String^ query = "SELECT DISTINCT at.termCode, at.termName "
                    "FROM academic_term at "
                    "INNER JOIN course_offering co ON at.termCode = co.termCode "
                    "INNER JOIN enrollment e ON co.id = e.courseOfferingID "
                    "WHERE e.studentID = @studentID "
                    "ORDER BY at.termCode DESC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                cmd->Parameters->AddWithValue("@studentID", this->studentID);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ table = gcnew DataTable();
                adapter->Fill(table);

                cmbTerm->DisplayMember = "termName";
                cmbTerm->ValueMember = "termCode";
                cmbTerm->DataSource = table;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading terms: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }
        }

        void LoadGrades(void)
        {
            try {
                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                String^ selectedTerm = cmbTerm->SelectedValue ? cmbTerm->SelectedValue->ToString() : "";

                String^ query = "SELECT termCode, courseCode, courseName, credits, grade, gradePoint, submissionDate "
                    "FROM student_grades "
                    "WHERE studentID = @studentID ";

                if (selectedTerm != "") {
                    query += "AND termCode = @termCode ";
                }
                query += "ORDER BY termCode DESC, courseCode";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                cmd->Parameters->AddWithValue("@studentID", this->studentID);

                if (selectedTerm != "") {
                    cmd->Parameters->AddWithValue("@termCode", selectedTerm);
                }

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ table = gcnew DataTable();
                adapter->Fill(table);

                dgvGrades->DataSource = table;

                // Calculate GPA
                double totalPoints = 0;
                int totalCredits = 0;

                for (int i = 0; i < table->Rows->Count; i++) {
                    DataRow^ row = table->Rows[i];
                    if (!Convert::IsDBNull(row["gradePoint"]) && !Convert::IsDBNull(row["credits"])) {
                        totalPoints += Convert::ToDouble(row["gradePoint"]) * Convert::ToInt32(row["credits"]);
                        totalCredits += Convert::ToInt32(row["credits"]);
                    }
                }

                double gpa = totalCredits > 0 ? totalPoints / totalCredits : 0;
                lblGPA->Text = String::Format("Term GPA: {0:F2}", gpa);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading grades: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }
        }

        System::Void cmbTerm_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
            LoadGrades();
        }
    };
}