// CourseManagementForm.h
#pragma once
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace MySql::Data::MySqlClient;

    public ref class CourseManagementForm : public System::Windows::Forms::Form {
    public:
        CourseManagementForm(String^ facultyID)
        {
            InitializeComponent();
            this->facultyID = facultyID;
            LoadCourseOfferings();
        }

    protected:
        ~CourseManagementForm()
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

        // Form controls
        System::Windows::Forms::DataGridView^ dgvCourses;
        System::Windows::Forms::ComboBox^ cmbTerm;
        System::Windows::Forms::ComboBox^ cmbStatus;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::GroupBox^ grpCourseDetails;
        System::Windows::Forms::Label^ lblCourse;
        System::Windows::Forms::Label^ lblSection;
        System::Windows::Forms::Label^ lblCapacity;
        System::Windows::Forms::Label^ lblStatus;
        System::Windows::Forms::ComboBox^ cmbCourse;
        System::Windows::Forms::TextBox^ txtSection;
        System::Windows::Forms::NumericUpDown^ numCapacity;
        System::Windows::Forms::GroupBox^ grpEnrolledStudents;
        System::Windows::Forms::DataGridView^ dgvStudents;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Text = L"Course Management";
            this->Size = System::Drawing::Size(1000, 700);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Initialize Term ComboBox
            this->cmbTerm = gcnew ComboBox();
            this->cmbTerm->Location = System::Drawing::Point(20, 20);
            this->cmbTerm->Size = System::Drawing::Size(200, 25);
            this->cmbTerm->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbTerm->SelectedIndexChanged += gcnew EventHandler(this, &CourseManagementForm::cmbTerm_SelectedIndexChanged);

            // Initialize Course GridView
            this->dgvCourses = gcnew DataGridView();
            this->dgvCourses->Location = System::Drawing::Point(20, 60);
            this->dgvCourses->Size = System::Drawing::Size(600, 250);
            this->dgvCourses->AllowUserToAddRows = false;
            this->dgvCourses->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvCourses->MultiSelect = false;
            this->dgvCourses->ReadOnly = true;
            this->dgvCourses->SelectionChanged += gcnew EventHandler(this, &CourseManagementForm::dgvCourses_SelectionChanged);

            // Initialize Course Details Group
            this->grpCourseDetails = gcnew GroupBox();
            this->grpCourseDetails->Text = L"Course Details";
            this->grpCourseDetails->Location = System::Drawing::Point(20, 320);
            this->grpCourseDetails->Size = System::Drawing::Size(600, 150);

            // Course Selection
            this->lblCourse = gcnew Label();
            this->lblCourse->Text = L"Course:";
            this->lblCourse->Location = System::Drawing::Point(20, 30);
            this->lblCourse->AutoSize = true;

            this->cmbCourse = gcnew ComboBox();
            this->cmbCourse->Location = System::Drawing::Point(100, 30);
            this->cmbCourse->Size = System::Drawing::Size(200, 25);
            this->cmbCourse->DropDownStyle = ComboBoxStyle::DropDownList;

            // Section
            this->lblSection = gcnew Label();
            this->lblSection->Text = L"Section:";
            this->lblSection->Location = System::Drawing::Point(320, 30);
            this->lblSection->AutoSize = true;

            this->txtSection = gcnew TextBox();
            this->txtSection->Location = System::Drawing::Point(400, 30);
            this->txtSection->Size = System::Drawing::Size(100, 25);

            // Capacity
            this->lblCapacity = gcnew Label();
            this->lblCapacity->Text = L"Capacity:";
            this->lblCapacity->Location = System::Drawing::Point(20, 70);
            this->lblCapacity->AutoSize = true;

            this->numCapacity = gcnew NumericUpDown();
            this->numCapacity->Location = System::Drawing::Point(100, 70);
            this->numCapacity->Size = System::Drawing::Size(100, 25);
            this->numCapacity->Minimum = 1;
            this->numCapacity->Maximum = 100;
            this->numCapacity->Value = 30;

            // Status
            this->lblStatus = gcnew Label();
            this->lblStatus->Text = L"Status:";
            this->lblStatus->Location = System::Drawing::Point(320, 70);
            this->lblStatus->AutoSize = true;

            this->cmbStatus = gcnew ComboBox();
            this->cmbStatus->Location = System::Drawing::Point(400, 70);
            this->cmbStatus->Size = System::Drawing::Size(150, 25);
            this->cmbStatus->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbStatus->Items->AddRange(gcnew array<String^> {
                "SCHEDULED", "IN_PROGRESS", "COMPLETED", "CANCELLED"
            });

            // Buttons
            this->btnAdd = gcnew Button();
            this->btnAdd->Text = L"Add Course";
            this->btnAdd->Location = System::Drawing::Point(20, 110);
            this->btnAdd->Size = System::Drawing::Size(100, 30);
            this->btnAdd->Click += gcnew EventHandler(this, &CourseManagementForm::btnAdd_Click);

            this->btnUpdate = gcnew Button();
            this->btnUpdate->Text = L"Update";
            this->btnUpdate->Location = System::Drawing::Point(130, 110);
            this->btnUpdate->Size = System::Drawing::Size(100, 30);
            this->btnUpdate->Click += gcnew EventHandler(this, &CourseManagementForm::btnUpdate_Click);

            this->btnDelete = gcnew Button();
            this->btnDelete->Text = L"Delete";
            this->btnDelete->Location = System::Drawing::Point(240, 110);
            this->btnDelete->Size = System::Drawing::Size(100, 30);
            this->btnDelete->Click += gcnew EventHandler(this, &CourseManagementForm::btnDelete_Click);

            // Add controls to Course Details Group
            this->grpCourseDetails->Controls->AddRange(gcnew array<Control^> {
                this->lblCourse, this->cmbCourse,
                    this->lblSection, this->txtSection,
                    this->lblCapacity, this->numCapacity,
                    this->lblStatus, this->cmbStatus,
                    this->btnAdd, this->btnUpdate, this->btnDelete
            });

            // Initialize Enrolled Students Group
            this->grpEnrolledStudents = gcnew GroupBox();
            this->grpEnrolledStudents->Text = L"Enrolled Students";
            this->grpEnrolledStudents->Location = System::Drawing::Point(20, 480);
            this->grpEnrolledStudents->Size = System::Drawing::Size(600, 150);

            // Initialize Students GridView
            this->dgvStudents = gcnew DataGridView();
            this->dgvStudents->Location = System::Drawing::Point(10, 20);
            this->dgvStudents->Size = System::Drawing::Size(580, 120);
            this->dgvStudents->AllowUserToAddRows = false;
            this->dgvStudents->ReadOnly = true;

            this->grpEnrolledStudents->Controls->Add(this->dgvStudents);

            // Add all controls to form
            this->Controls->AddRange(gcnew array<Control^> {
                this->cmbTerm,
                    this->dgvCourses,
                    this->grpCourseDetails,
                    this->grpEnrolledStudents
            });

            LoadTerms();
        }

        void LoadTerms()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT termCode, termName FROM academic_term WHERE isActive = 1 ORDER BY startDate";
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

        void LoadCourseOfferings()
        {
            if (cmbTerm->SelectedIndex == -1) return;

            try {
                String^ termCode = cmbTerm->SelectedItem->ToString()->Split('-')[0]->Trim();
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT co.id, c.courseCode, c.courseName, co.section, "
                    "co.capacity, co.enrolledCount, co.status "
                    "FROM course_offering co "
                    "JOIN course c ON co.courseCode = c.courseCode "
                    "WHERE co.facultyID = @facultyID AND co.termCode = @termCode";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@facultyID", facultyID);
                cmd->Parameters->AddWithValue("@termCode", termCode);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);

                dgvCourses->DataSource = dt;
                conn->Close();

                LoadAvailableCourses();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading course offerings: " + ex->Message);
            }
        }

        void LoadAvailableCourses()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT courseCode, courseName FROM course WHERE isActive = 1";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                MySqlDataReader^ reader = cmd->ExecuteReader();

                cmbCourse->Items->Clear();
                while (reader->Read()) {
                    String^ courseDisplay = String::Format("{0} - {1}",
                        reader["courseCode"]->ToString(),
                        reader["courseName"]->ToString());
                    cmbCourse->Items->Add(courseDisplay);
                }

                reader->Close();
                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading courses: " + ex->Message);
            }
        }

        void LoadEnrolledStudents(int courseOfferingID)
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ query = "SELECT s.studentID, u.firstName, u.lastName, es.statusName "
                    "FROM enrollment e "
                    "JOIN student s ON e.studentID = s.studentID "
                    "JOIN user u ON s.userID = u.userID "
                    "JOIN enrollment_status es ON e.statusID = es.id "
                    "WHERE e.courseOfferingID = @courseOfferingID";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);

                dgvStudents->DataSource = dt;
                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading enrolled students: " + ex->Message);
            }
        }

        // Event Handlers
        void cmbTerm_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
            LoadCourseOfferings();
        }

        void dgvCourses_SelectionChanged(Object^ sender, EventArgs^ e) {
            if (dgvCourses->SelectedRows->Count > 0) {
                DataGridViewRow^ row = dgvCourses->SelectedRows[0];
                int courseOfferingID = Convert::ToInt32(row->Cells["id"]->Value);
                LoadEnrolledStudents(courseOfferingID);

                // Populate form fields
                String^ courseCode = row->Cells["courseCode"]->Value->ToString();
                for each (String ^ item in cmbCourse->Items) {
                    if (item->StartsWith(courseCode)) {
                        cmbCourse->SelectedItem = item;
                        break;
                    }
                }

                txtSection->Text = row->Cells["section"]->Value->ToString();
                numCapacity->Value = Convert::ToInt32(row->Cells["capacity"]->Value);
                cmbStatus->Text = row->Cells["status"]->Value->ToString();

                btnAdd->Enabled = false;
                btnUpdate->Enabled = true;
                btnDelete->Enabled = true;
            }
            else {
                ClearForm();
            }
        }

        void ClearForm()
        {
            cmbCourse->SelectedIndex = -1;
            txtSection->Clear();
            numCapacity->Value = 30;
            cmbStatus->SelectedIndex = -1;
            btnAdd->Enabled = true;
            btnUpdate->Enabled = false;
            btnDelete->Enabled = false;
            dgvStudents->DataSource = nullptr;
        }

        void btnAdd_Click(Object^ sender, EventArgs^ e)
        {
            if (!ValidateInput()) return;

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ termCode = cmbTerm->SelectedItem->ToString()->Split('-')[0]->Trim();
                String^ courseCode = cmbCourse->SelectedItem->ToString()->Split('-')[0]->Trim();

                String^ query = "INSERT INTO course_offering (courseCode, termCode, facultyID, section, capacity, status) "
                    "VALUES (@courseCode, @termCode, @facultyID, @section, @capacity, @status)";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@courseCode", courseCode);
                cmd->Parameters->AddWithValue("@termCode", termCode);
                cmd->Parameters->AddWithValue("@facultyID", facultyID);
                cmd->Parameters->AddWithValue("@section", txtSection->Text);
                cmd->Parameters->AddWithValue("@capacity", numCapacity->Value);
                cmd->Parameters->AddWithValue("@status", cmbStatus->Text);

                cmd->ExecuteNonQuery();
                conn->Close();

                MessageBox::Show("Course offering added successfully!", "Success",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

                LoadCourseOfferings();
                ClearForm();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error adding course offering: " + ex->Message);
            }
        }

        void btnUpdate_Click(Object^ sender, EventArgs^ e)
        {
            if (!ValidateInput() || dgvCourses->SelectedRows->Count == 0) return;

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                int courseOfferingID = Convert::ToInt32(dgvCourses->SelectedRows[0]->Cells["id"]->Value);
                String^ courseCode = cmbCourse->SelectedItem->ToString()->Split('-')[0]->Trim();

                String^ query = "UPDATE course_offering SET "
                    "courseCode = @courseCode, "
                    "section = @section, "
                    "capacity = @capacity, "
                    "status = @status, "
                    "lastModified = CURRENT_TIMESTAMP "
                    "WHERE id = @id AND facultyID = @facultyID";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@courseCode", courseCode);
                cmd->Parameters->AddWithValue("@section", txtSection->Text);
                cmd->Parameters->AddWithValue("@capacity", numCapacity->Value);
                cmd->Parameters->AddWithValue("@status", cmbStatus->Text);
                cmd->Parameters->AddWithValue("@id", courseOfferingID);
                cmd->Parameters->AddWithValue("@facultyID", facultyID);

                if (cmd->ExecuteNonQuery() > 0) {
                    MessageBox::Show("Course offering updated successfully!", "Success",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                    LoadCourseOfferings();
                }
                else {
                    MessageBox::Show("Unable to update course offering. Please ensure you have the correct permissions.");
                }

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error updating course offering: " + ex->Message);
            }
        }

        void btnDelete_Click(Object^ sender, EventArgs^ e)
        {
            if (dgvCourses->SelectedRows->Count == 0) return;

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                int courseOfferingID = Convert::ToInt32(dgvCourses->SelectedRows[0]->Cells["id"]->Value);

                // First check if there are any enrollments
                String^ checkQuery = "SELECT COUNT(*) FROM enrollment WHERE courseOfferingID = @id";
                MySqlCommand^ checkCmd = gcnew MySqlCommand(checkQuery, conn);
                checkCmd->Parameters->AddWithValue("@id", courseOfferingID);

                int enrollmentCount = Convert::ToInt32(checkCmd->ExecuteScalar());
                if (enrollmentCount > 0) {
                    MessageBox::Show("Cannot delete course offering with existing enrollments. "
                        "Consider marking it as CANCELLED instead.", "Delete Failed",
                        MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }

                String^ deleteQuery = "DELETE FROM course_offering "
                    "WHERE id = @id AND facultyID = @facultyID";

                MySqlCommand^ deleteCmd = gcnew MySqlCommand(deleteQuery, conn);
                deleteCmd->Parameters->AddWithValue("@id", courseOfferingID);
                deleteCmd->Parameters->AddWithValue("@facultyID", facultyID);

                if (deleteCmd->ExecuteNonQuery() > 0) {
                    MessageBox::Show("Course offering deleted successfully!", "Success",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                    LoadCourseOfferings();
                    ClearForm();
                }
                else {
                    MessageBox::Show("Unable to delete course offering. Please ensure you have the correct permissions.");
                }

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error deleting course offering: " + ex->Message);
            }
        }

        bool ValidateInput()
        {
            if (cmbTerm->SelectedIndex == -1) {
                MessageBox::Show("Please select a term.");
                return false;
            }

            if (cmbCourse->SelectedIndex == -1) {
                MessageBox::Show("Please select a course.");
                return false;
            }

            if (String::IsNullOrWhiteSpace(txtSection->Text)) {
                MessageBox::Show("Please enter a section.");
                return false;
            }

            if (cmbStatus->SelectedIndex == -1) {
                MessageBox::Show("Please select a status.");
                return false;
            }

            return true;
        }
    };
}