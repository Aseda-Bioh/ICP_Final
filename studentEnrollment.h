#pragma once
#include <string>

namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    public ref class StudentEnrollmentForm : public System::Windows::Forms::Form
    {
    public:
        StudentEnrollmentForm(String^ studentID)
        {
            InitializeComponent();
            this->studentID = studentID;
            ConfigureDatabase();
            LoadAvailableCourses();
            LoadCurrentEnrollments();
        }

    protected:
        ~StudentEnrollmentForm()
        {
            if (components)
            {
                delete components;
            }
            if (sqlConnection)
            {
                sqlConnection->Close();
                delete sqlConnection;
            }
        }

    private:
        // Form components
        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridView^ dgvAvailableCourses;
        System::Windows::Forms::DataGridView^ dgvCurrentEnrollments;
        System::Windows::Forms::ComboBox^ cmbTerm;
        System::Windows::Forms::Button^ btnEnroll;
        System::Windows::Forms::Button^ btnWithdraw;
        System::Windows::Forms::Label^ lblAvailableCourses;
        System::Windows::Forms::Label^ lblCurrentEnrollments;
        System::Windows::Forms::Label^ lblTerm;

        // Database connection
        MySqlConnection^ sqlConnection;
        String^ connectString = "server=localhost;port=3306;database=university_system;uid=aseda;password=FatherAbraham2";
        String^ studentID;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // Form Configuration
            this->Text = L"Course Enrollment";
            this->Size = System::Drawing::Size(1000, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;

            // Term Selection ComboBox
            this->lblTerm = gcnew System::Windows::Forms::Label();
            this->lblTerm->Text = L"Select Term:";
            this->lblTerm->Location = System::Drawing::Point(20, 20);
            this->lblTerm->AutoSize = true;

            this->cmbTerm = gcnew System::Windows::Forms::ComboBox();
            this->cmbTerm->Location = System::Drawing::Point(100, 20);
            this->cmbTerm->Size = System::Drawing::Size(200, 25);
            this->cmbTerm->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbTerm->SelectedIndexChanged += gcnew EventHandler(this, &StudentEnrollmentForm::cmbTerm_SelectedIndexChanged);

            // Available Courses Grid
            this->lblAvailableCourses = gcnew System::Windows::Forms::Label();
            this->lblAvailableCourses->Text = L"Available Courses:";
            this->lblAvailableCourses->Location = System::Drawing::Point(20, 60);
            this->lblAvailableCourses->AutoSize = true;

            this->dgvAvailableCourses = gcnew System::Windows::Forms::DataGridView();
            this->dgvAvailableCourses->Location = System::Drawing::Point(20, 90);
            this->dgvAvailableCourses->Size = System::Drawing::Size(460, 400);
            this->dgvAvailableCourses->AllowUserToAddRows = false;
            this->dgvAvailableCourses->AllowUserToDeleteRows = false;
            this->dgvAvailableCourses->MultiSelect = false;
            this->dgvAvailableCourses->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvAvailableCourses->ReadOnly = true;

            // Current Enrollments Grid
            this->lblCurrentEnrollments = gcnew System::Windows::Forms::Label();
            this->lblCurrentEnrollments->Text = L"Current Enrollments:";
            this->lblCurrentEnrollments->Location = System::Drawing::Point(500, 60);
            this->lblCurrentEnrollments->AutoSize = true;

            this->dgvCurrentEnrollments = gcnew System::Windows::Forms::DataGridView();
            this->dgvCurrentEnrollments->Location = System::Drawing::Point(500, 90);
            this->dgvCurrentEnrollments->Size = System::Drawing::Size(460, 400);
            this->dgvCurrentEnrollments->AllowUserToAddRows = false;
            this->dgvCurrentEnrollments->AllowUserToDeleteRows = false;
            this->dgvCurrentEnrollments->MultiSelect = false;
            this->dgvCurrentEnrollments->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvCurrentEnrollments->ReadOnly = true;

            // Enroll Button
            this->btnEnroll = gcnew System::Windows::Forms::Button();
            this->btnEnroll->Text = L"Enroll";
            this->btnEnroll->Location = System::Drawing::Point(20, 500);
            this->btnEnroll->Size = System::Drawing::Size(100, 30);
            this->btnEnroll->Click += gcnew EventHandler(this, &StudentEnrollmentForm::btnEnroll_Click);

            // Withdraw Button
            this->btnWithdraw = gcnew System::Windows::Forms::Button();
            this->btnWithdraw->Text = L"Withdraw";
            this->btnWithdraw->Location = System::Drawing::Point(500, 500);
            this->btnWithdraw->Size = System::Drawing::Size(100, 30);
            this->btnWithdraw->Click += gcnew EventHandler(this, &StudentEnrollmentForm::btnWithdraw_Click);

            // Add controls to form
            this->Controls->Add(this->lblTerm);
            this->Controls->Add(this->cmbTerm);
            this->Controls->Add(this->lblAvailableCourses);
            this->Controls->Add(this->dgvAvailableCourses);
            this->Controls->Add(this->lblCurrentEnrollments);
            this->Controls->Add(this->dgvCurrentEnrollments);
            this->Controls->Add(this->btnEnroll);
            this->Controls->Add(this->btnWithdraw);
        }

        void ConfigureDatabase(void)
        {
            try {
                sqlConnection = gcnew MySqlConnection(connectString);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Database configuration error: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void LoadAvailableCourses(void)
        {
            try {
                String^ selectedTerm = cmbTerm->SelectedItem ? cmbTerm->SelectedItem->ToString() : "";
                if (String::IsNullOrEmpty(selectedTerm)) return;

                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                String^ query = "SELECT co.id, c.courseCode, c.courseName, c.credits, "
                    "co.section, co.capacity, co.enrolledCount, CONCAT(u.firstName, ' ', u.lastName) as facultyName "
                    "FROM course_offering co "
                    "INNER JOIN course c ON co.courseCode = c.courseCode "
                    "INNER JOIN faculty f ON co.facultyID = f.userID "
                    "INNER JOIN user u ON f.userID = u.userID "
                    "WHERE co.termCode = @termCode "
                    "AND co.enrolledCount < co.capacity "
                    "AND co.status = 'SCHEDULED' "
                    "AND NOT EXISTS ("
                    "SELECT 1 FROM enrollment e "
                    "WHERE e.courseOfferingID = co.id "
                    "AND e.studentID = @studentID "
                    "AND e.statusID = 1"  // Only exclude active enrollments (statusID = 1)
                    ")";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                cmd->Parameters->AddWithValue("@termCode", selectedTerm);
                cmd->Parameters->AddWithValue("@studentID", this->studentID);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ table = gcnew DataTable();
                adapter->Fill(table);

                dgvAvailableCourses->DataSource = table;
                FormatAvailableCoursesGrid();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading available courses: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Close();
            }
        }

        void LoadCurrentEnrollments(void)
        {
            try {
                String^ selectedTerm = cmbTerm->SelectedItem ? cmbTerm->SelectedItem->ToString() : "";
                if (String::IsNullOrEmpty(selectedTerm)) return;

                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                String^ query = "SELECT e.id as enrollmentID, c.courseCode, c.courseName, "
                    "c.credits, co.section, es.statusName as status "
                    "FROM enrollment e "
                    "INNER JOIN course_offering co ON e.courseOfferingID = co.id "
                    "INNER JOIN course c ON co.courseCode = c.courseCode "
                    "INNER JOIN enrollment_status es ON e.statusID = es.id "
                    "WHERE e.studentID = @studentID AND co.termCode = @termCode";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                cmd->Parameters->AddWithValue("@studentID", this->studentID);
                cmd->Parameters->AddWithValue("@termCode", selectedTerm);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ table = gcnew DataTable();
                adapter->Fill(table);

                dgvCurrentEnrollments->DataSource = table;
                FormatCurrentEnrollmentsGrid();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading current enrollments: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }
        }

        void LoadTerms(void)
        {
            MySqlDataReader^ reader = nullptr;
            try {
                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                String^ query = "SELECT termCode FROM academic_term WHERE isActive = true ORDER BY startDate";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                reader = cmd->ExecuteReader();

                cmbTerm->Items->Clear();
                while (reader->Read()) {
                    cmbTerm->Items->Add(reader["termCode"]->ToString());
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading terms: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (reader != nullptr && !reader->IsClosed)
                    reader->Close();
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }

            // Set selected index after closing the connection
            if (cmbTerm->Items->Count > 0)
                cmbTerm->SelectedIndex = 0;
        }

        void FormatAvailableCoursesGrid(void)
        {
            dgvAvailableCourses->Columns["id"]->Visible = false;
            dgvAvailableCourses->Columns["courseCode"]->HeaderText = "Course Code";
            dgvAvailableCourses->Columns["courseName"]->HeaderText = "Course Name";
            dgvAvailableCourses->Columns["credits"]->HeaderText = "Credits";
            dgvAvailableCourses->Columns["section"]->HeaderText = "Section";
            dgvAvailableCourses->Columns["capacity"]->HeaderText = "Capacity";
            dgvAvailableCourses->Columns["enrolledCount"]->HeaderText = "Enrolled";
            dgvAvailableCourses->Columns["facultyName"]->HeaderText = "Faculty";

            dgvAvailableCourses->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        }

        void FormatCurrentEnrollmentsGrid(void)
        {
            dgvCurrentEnrollments->Columns["enrollmentID"]->Visible = false;
            dgvCurrentEnrollments->Columns["courseCode"]->HeaderText = "Course Code";
            dgvCurrentEnrollments->Columns["courseName"]->HeaderText = "Course Name";
            dgvCurrentEnrollments->Columns["credits"]->HeaderText = "Credits";
            dgvCurrentEnrollments->Columns["section"]->HeaderText = "Section";
            dgvCurrentEnrollments->Columns["status"]->HeaderText = "Status";

            dgvCurrentEnrollments->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        }

        System::Void cmbTerm_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
            LoadAvailableCourses();
            LoadCurrentEnrollments();
        }

        System::Void btnEnroll_Click(System::Object^ sender, System::EventArgs^ e) {
            if (dgvAvailableCourses->SelectedRows->Count == 0) {
                MessageBox::Show("Please select a course to enroll in.",
                    "Enrollment Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try {
                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                // First check if student is already enrolled in another section of this course
                String^ courseCode = dgvAvailableCourses->SelectedRows[0]->Cells["courseCode"]->Value->ToString();
                String^ selectedTerm = cmbTerm->SelectedItem->ToString();

                String^ checkExistingQuery = "SELECT co.section "
                    "FROM enrollment e "
                    "INNER JOIN course_offering co ON e.courseOfferingID = co.id "
                    "WHERE e.studentID = @studentID "
                    "AND co.courseCode = @courseCode "
                    "AND co.termCode = @termCode "
                    "AND e.statusID = 1";  // Only check active enrollments

                MySqlCommand^ checkCmd = gcnew MySqlCommand(checkExistingQuery, sqlConnection);
                checkCmd->Parameters->AddWithValue("@studentID", this->studentID);
                checkCmd->Parameters->AddWithValue("@courseCode", courseCode);
                checkCmd->Parameters->AddWithValue("@termCode", selectedTerm);

                Object^ result = checkCmd->ExecuteScalar();

                if (result != nullptr) {
                    String^ currentSection = result->ToString();
                    MessageBox::Show(String::Format("You are already enrolled in section {0} of this course. Please withdraw from that section first if you wish to enroll in a different section.",
                        currentSection), "Enrollment Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                    return;
                }

                // If no existing enrollment, proceed with normal enrollment process
                // Start transaction
                MySqlTransaction^ transaction = sqlConnection->BeginTransaction();

                try {
                    int courseOfferingID = Convert::ToInt32(dgvAvailableCourses->SelectedRows[0]->Cells["id"]->Value);

                    // Check if the course is still available
                    String^ checkQuery = "SELECT capacity, enrolledCount FROM course_offering "
                        "WHERE id = @courseOfferingID FOR UPDATE";
                    MySqlCommand^ checkCapacityCmd = gcnew MySqlCommand(checkQuery, sqlConnection, transaction);
                    checkCapacityCmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);

                    MySqlDataReader^ reader = checkCapacityCmd->ExecuteReader();
                    if (reader->Read()) {
                        int capacity = Convert::ToInt32(reader["capacity"]);
                        int enrolled = Convert::ToInt32(reader["enrolledCount"]);

                        reader->Close();

                        if (enrolled >= capacity) {
                            transaction->Rollback();
                            MessageBox::Show("This course is now full.",
                                "Enrollment Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                            return;
                        }

                        // First check if there's an existing withdrawn enrollment that can be reactivated
                        String^ checkWithdrawnQuery = "SELECT id FROM enrollment "
                            "WHERE studentID = @studentID "
                            "AND courseOfferingID = @courseOfferingID "
                            "AND statusID = 2"; // Check for withdrawn status

                        MySqlCommand^ checkWithdrawnCmd = gcnew MySqlCommand(checkWithdrawnQuery, sqlConnection);
                        checkWithdrawnCmd->Parameters->AddWithValue("@studentID", this->studentID);
                        checkWithdrawnCmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);

                        Object^ withdrawnEnrollmentID = checkWithdrawnCmd->ExecuteScalar();

                        if (withdrawnEnrollmentID != nullptr) {
                            // Reactivate the withdrawn enrollment instead of creating a new one
                            String^ reactivateQuery = "UPDATE enrollment SET statusID = 1 WHERE id = @enrollmentID";
                            MySqlCommand^ reactivateCmd = gcnew MySqlCommand(reactivateQuery, sqlConnection, transaction);
                            reactivateCmd->Parameters->AddWithValue("@enrollmentID", withdrawnEnrollmentID);
                            reactivateCmd->ExecuteNonQuery();
                        }
                        else {
                            // Insert new enrollment record
                            String^ enrollQuery = "INSERT INTO enrollment (studentID, courseOfferingID, statusID) "
                                "VALUES (@studentID, @courseOfferingID, 1)";
                            MySqlCommand^ enrollCmd = gcnew MySqlCommand(enrollQuery, sqlConnection, transaction);
                            enrollCmd->Parameters->AddWithValue("@studentID", this->studentID);
                            enrollCmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);
                            enrollCmd->ExecuteNonQuery();
                        }

                        // Update enrolled count
                        String^ updateQuery = "UPDATE course_offering SET enrolledCount = enrolledCount + 1 "
                            "WHERE id = @courseOfferingID";
                        MySqlCommand^ updateCmd = gcnew MySqlCommand(updateQuery, sqlConnection, transaction);
                        updateCmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);
                        updateCmd->ExecuteNonQuery();

                        // Commit transaction
                        transaction->Commit();

                        MessageBox::Show("Successfully enrolled in the course.",
                            "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                        // Refresh grids
                        LoadAvailableCourses();
                        LoadCurrentEnrollments();
                    }
                    else {
                        reader->Close();
                        transaction->Rollback();
                        MessageBox::Show("Course not found.",
                            "Enrollment Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
                catch (Exception^ ex) {
                    transaction->Rollback();
                    throw ex;
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error during enrollment: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }
        }

        System::Void btnWithdraw_Click(System::Object^ sender, System::EventArgs^ e) {
            if (dgvCurrentEnrollments->SelectedRows->Count == 0) {
                MessageBox::Show("Please select a course to withdraw from.",
                    "Withdrawal Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try {
                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                // Start transaction
                MySqlTransaction^ transaction = sqlConnection->BeginTransaction();

                try {
                    int enrollmentID = Convert::ToInt32(dgvCurrentEnrollments->SelectedRows[0]->Cells["enrollmentID"]->Value);

                    // Get the course offering ID
                    String^ getOfferingQuery = "SELECT courseOfferingID FROM enrollment WHERE id = @enrollmentID";
                    MySqlCommand^ getOfferingCmd = gcnew MySqlCommand(getOfferingQuery, sqlConnection, transaction);
                    getOfferingCmd->Parameters->AddWithValue("@enrollmentID", enrollmentID);
                    Object^ courseOfferingID = getOfferingCmd->ExecuteScalar();

                    if (courseOfferingID != nullptr) {
                        // Update enrollment status to Withdrawn (status ID 2)
                        String^ withdrawQuery = "UPDATE enrollment SET statusID = 2 WHERE id = @enrollmentID";
                        MySqlCommand^ withdrawCmd = gcnew MySqlCommand(withdrawQuery, sqlConnection, transaction);
                        withdrawCmd->Parameters->AddWithValue("@enrollmentID", enrollmentID);
                        withdrawCmd->ExecuteNonQuery();

                        // Update enrolled count
                        String^ updateQuery = "UPDATE course_offering SET enrolledCount = enrolledCount - 1 "
                            "WHERE id = @courseOfferingID";
                        MySqlCommand^ updateCmd = gcnew MySqlCommand(updateQuery, sqlConnection, transaction);
                        updateCmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);
                        updateCmd->ExecuteNonQuery();

                        // Commit transaction
                        transaction->Commit();

                        MessageBox::Show("Successfully withdrawn from the course.",
                            "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

                        // Refresh grids
                        LoadAvailableCourses();
                        LoadCurrentEnrollments();
                    }
                    else {
                        transaction->Rollback();
                        MessageBox::Show("Enrollment record not found.",
                            "Withdrawal Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
                catch (Exception^ ex) {
                    transaction->Rollback();
                    throw ex;
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error during withdrawal: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }
        }

    public:
        // Override OnLoad to initialize the form
        virtual void OnLoad(EventArgs^ e) override {
            Form::OnLoad(e);
            LoadTerms();
        }
    };
}