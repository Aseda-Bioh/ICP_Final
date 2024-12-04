// ViewRosterForm.h
#pragma once

namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic; // Add this
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    public ref class ViewRosterForm : public System::Windows::Forms::Form
    {
    public:
        ViewRosterForm(String^ facultyID)
        {
            InitializeComponent();
            this->facultyID = facultyID;
            LoadCourses();
        }

    protected:
        ~ViewRosterForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        String^ facultyID;
        System::ComponentModel::Container^ components;

        // UI Controls
        ComboBox^ cmbTerms;
        ComboBox^ cmbCourses;
        DataGridView^ dgvRoster;
        Label^ lblTerm;
        Label^ lblCourse;
        Label^ lblStudentCount;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Text = L"View Class Roster";
            this->Size = System::Drawing::Size(800, 600);

            // Term Label and ComboBox
            this->lblTerm = gcnew Label();
            this->lblTerm->Text = L"Select Term:";
            this->lblTerm->Location = System::Drawing::Point(20, 20);
            this->lblTerm->Size = System::Drawing::Size(100, 20);

            this->cmbTerms = gcnew ComboBox();
            this->cmbTerms->Location = System::Drawing::Point(120, 20);
            this->cmbTerms->Size = System::Drawing::Size(200, 20);
            this->cmbTerms->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbTerms->SelectedIndexChanged += gcnew EventHandler(this, &ViewRosterForm::cmbTerms_SelectedIndexChanged);

            // Course Label and ComboBox
            this->lblCourse = gcnew Label();
            this->lblCourse->Text = L"Select Course:";
            this->lblCourse->Location = System::Drawing::Point(20, 50);
            this->lblCourse->Size = System::Drawing::Size(100, 20);

            this->cmbCourses = gcnew ComboBox();
            this->cmbCourses->Location = System::Drawing::Point(120, 50);
            this->cmbCourses->Size = System::Drawing::Size(200, 20);
            this->cmbCourses->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbCourses->SelectedIndexChanged += gcnew EventHandler(this, &ViewRosterForm::cmbCourses_SelectedIndexChanged);

            // Student Count Label
            this->lblStudentCount = gcnew Label();
            this->lblStudentCount->Text = L"Total Students: 0";
            this->lblStudentCount->Location = System::Drawing::Point(20, 80);
            this->lblStudentCount->Size = System::Drawing::Size(200, 20);

            // DataGridView for Roster
            this->dgvRoster = gcnew DataGridView();
            this->dgvRoster->Location = System::Drawing::Point(20, 110);
            this->dgvRoster->Size = System::Drawing::Size(740, 440);
            this->dgvRoster->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvRoster->AllowUserToAddRows = false;
            this->dgvRoster->AllowUserToDeleteRows = false;
            this->dgvRoster->ReadOnly = true;
            this->dgvRoster->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvRoster->MultiSelect = false;

            // Add controls to form
            this->Controls->Add(this->lblTerm);
            this->Controls->Add(this->cmbTerms);
            this->Controls->Add(this->lblCourse);
            this->Controls->Add(this->cmbCourses);
            this->Controls->Add(this->lblStudentCount);
            this->Controls->Add(this->dgvRoster);
        }

        void LoadCourses()
        {
            try {
                String^ connString = "Server=localhost;Database=university_system;Uid=root;Pwd=;";
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                // Load Terms
                String^ termQuery = "SELECT DISTINCT termCode, termName FROM academic_term WHERE isActive = 1 ORDER BY startDate DESC";
                MySqlCommand^ termCmd = gcnew MySqlCommand(termQuery, conn);
                MySqlDataReader^ termReader = termCmd->ExecuteReader();

                cmbTerms->Items->Clear();
                while (termReader->Read()) {
                    String^ termDisplay = String::Format("{0} - {1}",
                        termReader["termCode"]->ToString(),
                        termReader["termName"]->ToString());
                    cmbTerms->Items->Add(termDisplay);
                }
                termReader->Close();

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading terms: " + ex->Message);
            }
        }

        void LoadCourseOfferings(String^ termCode)
        {
            try {
                String^ connString = "Server=localhost;Database=university_system;Uid=root;Pwd=;";
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                // Modified query to get full course offering info
                String^ courseQuery = "SELECT co.id as offeringID, CONCAT(c.courseCode, ' - ', c.courseName, ' (Section ', co.section, ')') as courseInfo "
                    "FROM course_offering co "
                    "JOIN course c ON co.courseCode = c.courseCode "
                    "WHERE co.facultyID = @facultyID AND co.termCode = @termCode";

                MySqlCommand^ courseCmd = gcnew MySqlCommand(courseQuery, conn);
                courseCmd->Parameters->AddWithValue("@facultyID", facultyID);
                courseCmd->Parameters->AddWithValue("@termCode", termCode);

                MySqlDataReader^ courseReader = courseCmd->ExecuteReader();

                cmbCourses->Items->Clear();

                // Create a new dictionary for storing the mapping
                Dictionary<String^, int>^ courseMap = gcnew Dictionary<String^, int>();

                while (courseReader->Read()) {
                    String^ courseDisplay = courseReader["courseInfo"]->ToString();
                    int offeringID = Convert::ToInt32(courseReader["offeringID"]);
                    courseMap->Add(courseDisplay, offeringID);
                    cmbCourses->Items->Add(courseDisplay);
                }

                courseReader->Close();
                conn->Close();

                // Store the dictionary in the ComboBox's Tag property
                cmbCourses->Tag = courseMap;

            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading courses: " + ex->Message);
            }
        }

        void LoadRoster(int courseOfferingID)
        {
            try {
                String^ connString = "Server=localhost;Database=university_system;Uid=root;Pwd=;";
                MySqlConnection^ conn = gcnew MySqlConnection(connString);
                conn->Open();

                String^ rosterQuery = "SELECT u.userID, u.firstName, u.lastName, u.email, s.studentID, s.programCode, "
                    "es.statusName as enrollmentStatus, e.enrollmentDate "
                    "FROM enrollment e "
                    "JOIN student s ON e.studentID = s.studentID "
                    "JOIN user u ON s.userID = u.userID "
                    "JOIN enrollment_status es ON e.statusID = es.id "
                    "WHERE e.courseOfferingID = @courseOfferingID "
                    "ORDER BY u.lastName, u.firstName";

                MySqlCommand^ rosterCmd = gcnew MySqlCommand(rosterQuery, conn);
                rosterCmd->Parameters->AddWithValue("@courseOfferingID", courseOfferingID);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(rosterCmd);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);

                dgvRoster->DataSource = dt;
                lblStudentCount->Text = String::Format("Total Students: {0}", dt->Rows->Count);

                // Debug message
                MessageBox::Show("Loaded " + dt->Rows->Count.ToString() + " students for course offering ID " + courseOfferingID);

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading roster: " + ex->Message + "\nStack trace: " + ex->StackTrace);
            }
        }

        System::Void cmbTerms_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (cmbTerms->SelectedIndex >= 0) {
                String^ selectedTerm = cmbTerms->SelectedItem->ToString();
                String^ termCode = selectedTerm->Split('-')[0]->Trim();
                LoadCourseOfferings(termCode);
            }
        }

        System::Void cmbCourses_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (cmbCourses->SelectedIndex >= 0) {
                try {
                    String^ selectedCourse = cmbCourses->SelectedItem->ToString();
                    Dictionary<String^, int>^ courseMap = safe_cast<Dictionary<String^, int>^>(cmbCourses->Tag);

                    if (courseMap->ContainsKey(selectedCourse)) {
                        int courseOfferingID = courseMap[selectedCourse];
                        LoadRoster(courseOfferingID);
                    }
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Error loading roster: " + ex->Message);
                }
            }
        }
    };
}