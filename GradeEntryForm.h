#pragma once
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace MySql::Data::MySqlClient;
    using namespace System::Drawing;

    public ref class GradeEntryForm : public System::Windows::Forms::Form {
    public:
        GradeEntryForm(String^ facultyID)
        {
            InitializeComponent();
            this->facultyID = facultyID;
            LoadTerms();
        }

    protected:
        ~GradeEntryForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        String^ facultyID;
        String^ connString = "Server=localhost;Database=university_system;Uid=root;Pwd=;";
        Dictionary<String^, int>^ courseOfferingIDs;

        // Form controls
        System::Windows::Forms::ComboBox^ cmbTerm;
        System::Windows::Forms::ComboBox^ cmbCourse;
        System::Windows::Forms::DataGridView^ dgvStudents;
        System::Windows::Forms::GroupBox^ grpGradeEntry;
        System::Windows::Forms::ComboBox^ cmbGrade;
        System::Windows::Forms::TextBox^ txtComments;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Label^ lblTerm;
        System::Windows::Forms::Label^ lblCourse;
        System::Windows::Forms::Label^ lblGrade;
        System::Windows::Forms::Label^ lblComments;
        System::Windows::Forms::Label^ lblStudentInfo;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Text = L"Grade Entry";
            this->Size = System::Drawing::Size(1000, 600);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Initialize collections
            this->courseOfferingIDs = gcnew Dictionary<String^, int>();

            // Initialize Term ComboBox
            this->lblTerm = gcnew Label();
            this->lblTerm->Text = L"Select Term:";
            this->lblTerm->Location = System::Drawing::Point(20, 20);
            this->lblTerm->AutoSize = true;

            this->cmbTerm = gcnew ComboBox();
            this->cmbTerm->Location = System::Drawing::Point(120, 20);
            this->cmbTerm->Size = System::Drawing::Size(200, 25);
            this->cmbTerm->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbTerm->SelectedIndexChanged += gcnew EventHandler(this, &GradeEntryForm::cmbTerm_SelectedIndexChanged);

            // Initialize Course ComboBox
            this->lblCourse = gcnew Label();
            this->lblCourse->Text = L"Select Course:";
            this->lblCourse->Location = System::Drawing::Point(350, 20);
            this->lblCourse->AutoSize = true;

            this->cmbCourse = gcnew ComboBox();
            this->cmbCourse->Location = System::Drawing::Point(450, 20);
            this->cmbCourse->Size = System::Drawing::Size(300, 25);
            this->cmbCourse->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbCourse->SelectedIndexChanged += gcnew EventHandler(this, &GradeEntryForm::cmbCourse_SelectedIndexChanged);

            // Initialize Student Grid
            this->dgvStudents = gcnew DataGridView();
            this->dgvStudents->Location = System::Drawing::Point(20, 60);
            this->dgvStudents->Size = System::Drawing::Size(730, 300);
            this->dgvStudents->AllowUserToAddRows = false;
            this->dgvStudents->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvStudents->MultiSelect = false;
            this->dgvStudents->ReadOnly = true;
            this->dgvStudents->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvStudents->SelectionChanged += gcnew EventHandler(this, &GradeEntryForm::dgvStudents_SelectionChanged);

            // Initialize Grade Entry Group
            this->grpGradeEntry = gcnew GroupBox();
            this->grpGradeEntry->Text = L"Grade Entry";
            this->grpGradeEntry->Location = System::Drawing::Point(20, 370);
            this->grpGradeEntry->Size = System::Drawing::Size(730, 150);

            // Student Info Label
            this->lblStudentInfo = gcnew Label();
            this->lblStudentInfo->Location = System::Drawing::Point(20, 30);
            this->lblStudentInfo->AutoSize = true;
            this->lblStudentInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, FontStyle::Bold));

            // Grade Selection
            this->lblGrade = gcnew Label();
            this->lblGrade->Text = L"Grade:";
            this->lblGrade->Location = System::Drawing::Point(20, 60);
            this->lblGrade->AutoSize = true;

            this->cmbGrade = gcnew ComboBox();
            this->cmbGrade->Location = System::Drawing::Point(100, 60);
            this->cmbGrade->Size = System::Drawing::Size(100, 25);
            this->cmbGrade->DropDownStyle = ComboBoxStyle::DropDownList;

            // Comments
            this->lblComments = gcnew Label();
            this->lblComments->Text = L"Comments:";
            this->lblComments->Location = System::Drawing::Point(220, 60);
            this->lblComments->AutoSize = true;

            this->txtComments = gcnew TextBox();
            this->txtComments->Location = System::Drawing::Point(300, 60);
            this->txtComments->Size = System::Drawing::Size(400, 50);
            this->txtComments->Multiline = true;

            // Buttons
            this->btnSave = gcnew Button();
            this->btnSave->Text = L"Save Grade";
            this->btnSave->Location = System::Drawing::Point(500, 100);
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Click += gcnew EventHandler(this, &GradeEntryForm::btnSave_Click);

            this->btnUpdate = gcnew Button();
            this->btnUpdate->Text = L"Update Grade";
            this->btnUpdate->Location = System::Drawing::Point(610, 100);
            this->btnUpdate->Size = System::Drawing::Size(100, 30);
            this->btnUpdate->Click += gcnew EventHandler(this, &GradeEntryForm::btnUpdate_Click);
            this->btnUpdate->Enabled = false;

            // Add controls to Grade Entry Group
            this->grpGradeEntry->Controls->AddRange(gcnew array<Control^> {
                this->lblStudentInfo,
                    this->lblGrade,
                    this->cmbGrade,
                    this->lblComments,
                    this->txtComments,
                    this->btnSave,
                    this->btnUpdate
            });

            // Add all controls to form
            this->Controls->AddRange(gcnew array<Control^> {
                this->lblTerm,
                    this->cmbTerm,
                    this->lblCourse,
                    this->cmbCourse,
                    this->dgvStudents,
                    this->grpGradeEntry
            });

            // Load grade scale
            LoadGradeScale();
        }

        void LoadTerms()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT termCode, termName FROM academic_term WHERE isActive = 1 ORDER BY startDate DESC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                cmbTerm->Items->Clear();
                while (reader->Read()) {
                    String^ termDisplay = String::Format("{0} - {1}",
                        reader["termCode"]->ToString(),
                        reader["termName"]->ToString());
                    cmbTerm->Items->Add(termDisplay);
                }

                reader->Close();
                conn->Close();

                if (cmbTerm->Items->Count > 0)
                    cmbTerm->SelectedIndex = 0;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading terms: " + ex->Message);
            }
        }

        void LoadCourses()
        {
            if (cmbTerm->SelectedIndex == -1) return;

            try {
                String^ termCode = cmbTerm->SelectedItem->ToString()->Split('-')[0]->Trim();
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT co.id AS courseOfferingID, "
                    "CONCAT(c.courseCode, ' - ', c.courseName, ' (Section ', co.section, ')') AS courseDisplay "
                    "FROM course_offering co "
                    "JOIN course c ON co.courseCode = c.courseCode "
                    "WHERE co.facultyID = @facultyID "
                    "AND co.termCode = @termCode "
                    "AND co.status IN ('SCHEDULED', 'IN_PROGRESS') "
                    "ORDER BY c.courseCode, co.section";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@facultyID", facultyID);
                cmd->Parameters->AddWithValue("@termCode", termCode);

                MySqlDataReader^ reader = cmd->ExecuteReader();

                cmbCourse->Items->Clear();
                courseOfferingIDs->Clear();

                while (reader->Read()) {
                    int courseOfferingID = Convert::ToInt32(reader["courseOfferingID"]);
                    String^ courseDisplay = reader["courseDisplay"]->ToString();
                    cmbCourse->Items->Add(courseDisplay);
                    courseOfferingIDs->Add(courseDisplay, courseOfferingID);
                }

                reader->Close();
                conn->Close();

                if (cmbCourse->Items->Count > 0)
                    cmbCourse->SelectedIndex = 0;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading courses: " + ex->Message);
            }
        }

        void LoadGradeScale()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT grade, description FROM grade_scale ORDER BY gradePoint DESC";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                cmbGrade->Items->Clear();
                while (reader->Read()) {
                    String^ gradeDisplay = String::Format("{0} - {1}",
                        reader["grade"]->ToString(),
                        reader["description"]->ToString());
                    cmbGrade->Items->Add(gradeDisplay);
                }

                reader->Close();
                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading grade scale: " + ex->Message);
            }
        }

        void LoadStudents()
        {
            if (cmbCourse->SelectedIndex == -1) return;

            try {
                String^ selectedCourse = cmbCourse->SelectedItem->ToString();
                int courseOfferingID = courseOfferingIDs[selectedCourse];

                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT e.id AS enrollmentID, s.studentID, u.firstName, u.lastName, "
                    "ap.programName, es.statusName AS enrollmentStatus, "
                    "COALESCE(g.grade, '') AS grade, COALESCE(g.comments, '') AS comments "
                    "FROM enrollment e "
                    "JOIN student s ON e.studentID = s.studentID "
                    "JOIN user u ON s.userID = u.userID "
                    "JOIN academic_program ap ON s.programCode = ap.programCode "
                    "JOIN enrollment_status es ON e.statusID = es.id "
                    "LEFT JOIN grade g ON e.id = g.enrollmentID "
                    "WHERE e.courseOfferingID = @courseOfferingID "
                    "AND e.statusID = 1 "  // Only show currently enrolled students
                    "ORDER BY u.lastName, u.firstName";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);

                dgvStudents->DataSource = dt;

                // Configure grid columns
                dgvStudents->Columns["enrollmentID"]->Visible = false;
                dgvStudents->Columns["studentID"]->HeaderText = "Student ID";
                dgvStudents->Columns["firstName"]->HeaderText = "First Name";
                dgvStudents->Columns["lastName"]->HeaderText = "Last Name";
                dgvStudents->Columns["programName"]->HeaderText = "Program";
                dgvStudents->Columns["enrollmentStatus"]->HeaderText = "Status";
                dgvStudents->Columns["grade"]->HeaderText = "Grade";
                dgvStudents->Columns["comments"]->HeaderText = "Comments";

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading students: " + ex->Message);
            }
        }

        void cmbTerm_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
            LoadCourses();
        }

        void cmbCourse_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
            LoadStudents();
        }

        void dgvStudents_SelectionChanged(Object^ sender, EventArgs^ e) {
            if (dgvStudents->SelectedRows->Count > 0) {
                DataGridViewRow^ row = dgvStudents->SelectedRows[0];
                String^ studentName = String::Format("{0} {1}",
                    row->Cells["firstName"]->Value->ToString(),
                    row->Cells["lastName"]->Value->ToString());

                lblStudentInfo->Text = String::Format("Student: {0} (ID: {1})",
                    studentName,
                    row->Cells["studentID"]->Value->ToString());

                String^ grade = row->Cells["grade"]->Value->ToString();
                if (!String::IsNullOrEmpty(grade)) {
                    String^ comments = row->Cells["comments"]->Value->ToString();

                    // Find and select the grade in combobox
                    for each (String ^ item in cmbGrade->Items) {
                        if (item->StartsWith(grade)) {
                            cmbGrade->SelectedItem = item;
                            break;
                        }
                    }

                    txtComments->Text = comments;
                    btnSave->Enabled = false;
                    btnUpdate->Enabled = true;
                }
                else {
                    cmbGrade->SelectedIndex = -1;
                    txtComments->Clear();
                    btnSave->Enabled = true;
                    btnUpdate->Enabled = false;
                }
            }
        }

        void btnSave_Click(Object^ sender, EventArgs^ e) {
            if (!ValidateInput()) return;

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "INSERT INTO grade (enrollmentID, grade, comments, submittedBy) "
                    "VALUES (@enrollmentID, @grade, @comments, @facultyID)";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                DataGridViewRow^ row = dgvStudents->SelectedRows[0];

                cmd->Parameters->AddWithValue("@enrollmentID", Convert::ToInt32(row->Cells["enrollmentID"]->Value));
                cmd->Parameters->AddWithValue("@grade", cmbGrade->SelectedItem->ToString()->Split('-')[0]->Trim());
                cmd->Parameters->AddWithValue("@comments", txtComments->Text);
                cmd->Parameters->AddWithValue("@facultyID", facultyID);

                cmd->ExecuteNonQuery();
                conn->Close();

                MessageBox::Show("Grade saved successfully!", "Success",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

                LoadStudents();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error saving grade: " + ex->Message);
            }
        }

        void btnUpdate_Click(Object^ sender, EventArgs^ e) {
            if (!ValidateInput()) return;

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "UPDATE grade SET "
                    "grade = @grade, "
                    "comments = @comments, "
                    "lastModified = CURRENT_TIMESTAMP "
                    "WHERE enrollmentID = @enrollmentID AND submittedBy = @facultyID";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                DataGridViewRow^ row = dgvStudents->SelectedRows[0];

                cmd->Parameters->AddWithValue("@enrollmentID", Convert::ToInt32(row->Cells["enrollmentID"]->Value));
                cmd->Parameters->AddWithValue("@grade", cmbGrade->SelectedItem->ToString()->Split('-')[0]->Trim());
                cmd->Parameters->AddWithValue("@comments", txtComments->Text);
                cmd->Parameters->AddWithValue("@facultyID", facultyID);

                if (cmd->ExecuteNonQuery() > 0) {
                    MessageBox::Show("Grade updated successfully!", "Success",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                    LoadStudents();
                }
                else {
                    MessageBox::Show("Unable to update grade. Please ensure you have the correct permissions.");
                }

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error updating grade: " + ex->Message);
            }
        }

        bool ValidateInput()
        {
            if (dgvStudents->SelectedRows->Count == 0) {
                MessageBox::Show("Please select a student.");
                return false;
            }

            if (cmbGrade->SelectedIndex == -1) {
                MessageBox::Show("Please select a grade.");
                return false;
            }

            DataGridViewRow^ row = dgvStudents->SelectedRows[0];
            String^ enrollmentStatus = row->Cells["enrollmentStatus"]->Value->ToString();

            if (enrollmentStatus != "ENROLLED") {
                MessageBox::Show("Can only enter grades for currently enrolled students.");
                return false;
            }

            return true;
        }
    };
}