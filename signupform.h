#pragma once
#include "login.h"
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    public ref class SignUpForm : public System::Windows::Forms::Form
    {
    private:
        // Form components
        System::Windows::Forms::Panel^ headerPanel;
        System::Windows::Forms::Panel^ mainPanel;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblFirstName;
        System::Windows::Forms::Label^ lblLastName;
        System::Windows::Forms::Label^ lblEmail;
        System::Windows::Forms::Label^ lblUsername;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::Label^ lblConfirmPassword;
        System::Windows::Forms::Label^ lblRole;
        System::Windows::Forms::TextBox^ txtFirstName;
        System::Windows::Forms::TextBox^ txtLastName;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::TextBox^ txtConfirmPassword;
        System::Windows::Forms::ComboBox^ cmbRole;
        System::Windows::Forms::Button^ btnSignUp;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::LinkLabel^ lnkLogin;
        System::ComponentModel::Container^ components;

        // Student specific controls
        System::Windows::Forms::Panel^ studentPanel;
        System::Windows::Forms::Label^ lblProgram;
        System::Windows::Forms::ComboBox^ cmbProgram;
        System::Windows::Forms::Label^ lblBatch;
        System::Windows::Forms::TextBox^ txtBatch;

        // Faculty specific controls
        System::Windows::Forms::Panel^ facultyPanel;
        System::Windows::Forms::Label^ lblDepartment;
        System::Windows::Forms::ComboBox^ cmbDepartment;
        System::Windows::Forms::Label^ lblSpecialization;
        System::Windows::Forms::TextBox^ txtSpecialization;

        // Database connection
        MySqlConnection^ sqlConnection;
        String^ connectString = "server=localhost;port=3306;database=university_system;uid=aseda;password=FatherAbraham2";

        LoginForm^ logForm = gcnew LoginForm();
    public:
        SignUpForm(void)
        {
            InitializeComponent();
            ConfigureDatabase();
            LoadDepartments();
            LoadPrograms();
        }

    protected:
        ~SignUpForm()
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
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // Form Configuration
            this->Text = L"Sign Up - University Management System";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Size = System::Drawing::Size(600, 800);
            this->BackColor = System::Drawing::Color::White;

            // Header Panel
            this->headerPanel = gcnew Panel();
            this->headerPanel->BackColor = System::Drawing::Color::FromArgb(0, 71, 160);
            this->headerPanel->Dock = DockStyle::Top;
            this->headerPanel->Height = 80;

            // Title
            this->lblTitle = gcnew Label();
            this->lblTitle->Text = L"Create New Account";
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->Font = gcnew System::Drawing::Font("Arial", 20, FontStyle::Bold);
            this->lblTitle->AutoSize = false;
            this->lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            this->lblTitle->Dock = DockStyle::Fill;
            this->headerPanel->Controls->Add(this->lblTitle);

            // Main Panel
            this->mainPanel = gcnew Panel();
            this->mainPanel->AutoScroll = true;
            this->mainPanel->Padding = System::Windows::Forms::Padding(40);
            this->mainPanel->Location = System::Drawing::Point(0, 80);
            this->mainPanel->Size = System::Drawing::Size(600, 720);

            // Basic Information Controls
            InitializeBasicControls();

            // Role Selection
            this->lblRole = gcnew Label();
            this->lblRole->Text = L"Role:";
            this->lblRole->Location = Point(40, 280);
            this->lblRole->AutoSize = true;
            this->lblRole->Font = gcnew System::Drawing::Font("Arial", 10);

            this->cmbRole = gcnew ComboBox();
            this->cmbRole->Location = Point(40, 300);
            this->cmbRole->Size = System::Drawing::Size(200, 25);
            this->cmbRole->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbRole->Items->AddRange(gcnew cli::array<Object^> { "Student", "Faculty" });
            this->cmbRole->SelectedIndexChanged += gcnew EventHandler(this, &SignUpForm::cmbRole_SelectedIndexChanged);

            // Initialize Role-specific panels
            InitializeStudentPanel();
            InitializeFacultyPanel();

            // Sign Up Button
            this->btnSignUp = gcnew Button();
            this->btnSignUp->Text = L"Sign Up";
            this->btnSignUp->Location = Point(40, 600);
            this->btnSignUp->Size = System::Drawing::Size(200, 40);
            this->btnSignUp->BackColor = System::Drawing::Color::FromArgb(0, 71, 160);
            this->btnSignUp->ForeColor = System::Drawing::Color::White;
            this->btnSignUp->FlatStyle = FlatStyle::Flat;
            this->btnSignUp->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            this->btnSignUp->Click += gcnew EventHandler(this, &SignUpForm::btnSignUp_Click);

            // Cancel Button
            this->btnCancel = gcnew Button();
            this->btnCancel->Text = L"Cancel";
            this->btnCancel->Location = Point(260, 600);
            this->btnCancel->Size = System::Drawing::Size(200, 40);
            this->btnCancel->BackColor = System::Drawing::Color::White;
            this->btnCancel->ForeColor = System::Drawing::Color::FromArgb(0, 71, 160);
            this->btnCancel->FlatStyle = FlatStyle::Flat;
            this->btnCancel->Font = gcnew System::Drawing::Font("Arial", 12);
            this->btnCancel->Click += gcnew EventHandler(this, &SignUpForm::btnCancel_Click);

            // Login Link
            this->lnkLogin = gcnew LinkLabel();
            this->lnkLogin->Text = L"Already have an account? Login here";
            this->lnkLogin->Location = Point(150, 650);
            this->lnkLogin->AutoSize = true;
            this->lnkLogin->Font = gcnew System::Drawing::Font("Arial", 10);
            this->lnkLogin->LinkClicked += gcnew LinkLabelLinkClickedEventHandler(this, &SignUpForm::lnkLogin_LinkClicked);

            // Add controls to panels and form
            this->Controls->Add(this->headerPanel);
            this->mainPanel->Controls->Add(this->lblRole);
            this->mainPanel->Controls->Add(this->cmbRole);
            this->mainPanel->Controls->Add(this->studentPanel);
            this->mainPanel->Controls->Add(this->facultyPanel);
            this->mainPanel->Controls->Add(this->btnSignUp);
            this->mainPanel->Controls->Add(this->btnCancel);
            this->mainPanel->Controls->Add(this->lnkLogin);
            this->Controls->Add(this->mainPanel);
        }

        void InitializeBasicControls(void)
        {
            // First Name
            this->lblFirstName = gcnew Label();
            this->lblFirstName->Text = L"First Name:";
            this->lblFirstName->Location = Point(40, 40);
            this->lblFirstName->AutoSize = true;
            this->lblFirstName->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtFirstName = gcnew TextBox();
            this->txtFirstName->Location = Point(40, 60);
            this->txtFirstName->Size = System::Drawing::Size(200, 25);

            // Last Name
            this->lblLastName = gcnew Label();
            this->lblLastName->Text = L"Last Name:";
            this->lblLastName->Location = Point(260, 40);
            this->lblLastName->AutoSize = true;
            this->lblLastName->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtLastName = gcnew TextBox();
            this->txtLastName->Location = Point(260, 60);
            this->txtLastName->Size = System::Drawing::Size(200, 25);

            // Email
            this->lblEmail = gcnew Label();
            this->lblEmail->Text = L"Email:";
            this->lblEmail->Location = Point(40, 100);
            this->lblEmail->AutoSize = true;
            this->lblEmail->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtEmail = gcnew TextBox();
            this->txtEmail->Location = Point(40, 120);
            this->txtEmail->Size = System::Drawing::Size(420, 25);

            // Username
            this->lblUsername = gcnew Label();
            this->lblUsername->Text = L"Username:";
            this->lblUsername->Location = Point(40, 160);
            this->lblUsername->AutoSize = true;
            this->lblUsername->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtUsername = gcnew TextBox();
            this->txtUsername->Location = Point(40, 180);
            this->txtUsername->Size = System::Drawing::Size(200, 25);

            // Password
            this->lblPassword = gcnew Label();
            this->lblPassword->Text = L"Password:";
            this->lblPassword->Location = Point(40, 220);
            this->lblPassword->AutoSize = true;
            this->lblPassword->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtPassword = gcnew TextBox();
            this->txtPassword->Location = Point(40, 240);
            this->txtPassword->Size = System::Drawing::Size(200, 25);
            this->txtPassword->PasswordChar = '•';

            // Confirm Password
            this->lblConfirmPassword = gcnew Label();
            this->lblConfirmPassword->Text = L"Confirm Password:";
            this->lblConfirmPassword->Location = Point(260, 220);
            this->lblConfirmPassword->AutoSize = true;
            this->lblConfirmPassword->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtConfirmPassword = gcnew TextBox();
            this->txtConfirmPassword->Location = Point(260, 240);
            this->txtConfirmPassword->Size = System::Drawing::Size(200, 25);
            this->txtConfirmPassword->PasswordChar = '•';

            // Add basic controls to main panel
            this->mainPanel->Controls->Add(this->lblFirstName);
            this->mainPanel->Controls->Add(this->txtFirstName);
            this->mainPanel->Controls->Add(this->lblLastName);
            this->mainPanel->Controls->Add(this->txtLastName);
            this->mainPanel->Controls->Add(this->lblEmail);
            this->mainPanel->Controls->Add(this->txtEmail);
            this->mainPanel->Controls->Add(this->lblUsername);
            this->mainPanel->Controls->Add(this->txtUsername);
            this->mainPanel->Controls->Add(this->lblPassword);
            this->mainPanel->Controls->Add(this->txtPassword);
            this->mainPanel->Controls->Add(this->lblConfirmPassword);
            this->mainPanel->Controls->Add(this->txtConfirmPassword);
        }

        void InitializeStudentPanel(void)
        {
            this->studentPanel = gcnew Panel();
            this->studentPanel->Location = Point(40, 340);
            this->studentPanel->Size = System::Drawing::Size(420, 240);
            this->studentPanel->Visible = false;

            // Program Selection
            this->lblProgram = gcnew Label();
            this->lblProgram->Text = L"Program:";
            this->lblProgram->Location = Point(0, 0);
            this->lblProgram->AutoSize = true;
            this->lblProgram->Font = gcnew System::Drawing::Font("Arial", 10);

            this->cmbProgram = gcnew ComboBox();
            this->cmbProgram->Location = Point(0, 20);
            this->cmbProgram->Size = System::Drawing::Size(420, 25);
            this->cmbProgram->DropDownStyle = ComboBoxStyle::DropDownList;

            // Batch
            this->lblBatch = gcnew Label();
            this->lblBatch->Text = L"Batch:";
            this->lblBatch->Location = Point(0, 60);
            this->lblBatch->AutoSize = true;
            this->lblBatch->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtBatch = gcnew TextBox();
            this->txtBatch->Location = Point(0, 80);
            this->txtBatch->Size = System::Drawing::Size(200, 25);

            // Add controls to student panel
            this->studentPanel->Controls->Add(this->lblProgram);
            this->studentPanel->Controls->Add(this->cmbProgram);
            this->studentPanel->Controls->Add(this->lblBatch);
            this->studentPanel->Controls->Add(this->txtBatch);
        }

        void InitializeFacultyPanel(void)
        {
            this->facultyPanel = gcnew Panel();
            this->facultyPanel->Location = Point(40, 340);
            this->facultyPanel->Size = System::Drawing::Size(420, 240);
            this->facultyPanel->Visible = false;

            // Department Selection
            this->lblDepartment = gcnew Label();
            this->lblDepartment->Text = L"Department:";
            this->lblDepartment->Location = Point(0, 0);
            this->lblDepartment->AutoSize = true;
            this->lblDepartment->Font = gcnew System::Drawing::Font("Arial", 10);

            this->cmbDepartment = gcnew ComboBox();
            this->cmbDepartment->Location = Point(0, 20);
            this->cmbDepartment->Size = System::Drawing::Size(420, 25);
            this->cmbDepartment->DropDownStyle = ComboBoxStyle::DropDownList;

            // Specialization
            this->lblSpecialization = gcnew Label();
            this->lblSpecialization->Text = L"Specialization:";
            this->lblSpecialization->Location = Point(0, 60);
            this->lblSpecialization->AutoSize = true;
            this->lblSpecialization->Font = gcnew System::Drawing::Font("Arial", 10);

            this->txtSpecialization = gcnew TextBox();
            this->txtSpecialization->Location = Point(0, 80);
            this->txtSpecialization->Size = System::Drawing::Size(420, 25);

            // Add controls to faculty panel
            this->facultyPanel->Controls->Add(this->lblDepartment);
            this->facultyPanel->Controls->Add(this->cmbDepartment);
            this->facultyPanel->Controls->Add(this->lblSpecialization);
            this->facultyPanel->Controls->Add(this->txtSpecialization);
        }

        void ConfigureDatabase(void)
        {
            try {
                sqlConnection = gcnew MySqlConnection(connectString);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Database configuration error: " + ex->Message);
            }
        }

        void LoadDepartments(void)
        {
            try {
                if (sqlConnection->State == ConnectionState::Closed) {
                    sqlConnection->Open();
                }

                String^ query = "SELECT departmentCode, departmentName FROM DEPARTMENT WHERE isActive = true";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);

                cmbDepartment->DisplayMember = "departmentName";
                cmbDepartment->ValueMember = "departmentCode";
                cmbDepartment->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading departments: " + ex->Message);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open) {
                    sqlConnection->Close();
                }
            }
        }

        void LoadPrograms(void)
        {
            try {
                if (sqlConnection->State == ConnectionState::Closed) {
                    sqlConnection->Open();
                }

                String^ query = "SELECT programCode, programName FROM ACADEMIC_PROGRAM WHERE isActive = TRUE";
                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);

                // Set data source for the program combo box
                cmbProgram->DisplayMember = "programName";
                cmbProgram->ValueMember = "programCode";
                cmbProgram->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading programs: " + ex->Message);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open) {
                    sqlConnection->Close();
                }
            }
        }

        void cmbRole_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (cmbRole->SelectedIndex == 0) { // Student
                studentPanel->Visible = true;
                facultyPanel->Visible = false;
            }
            else if (cmbRole->SelectedIndex == 1) { // Faculty
                studentPanel->Visible = false;
                facultyPanel->Visible = true;
            }
        }

        bool ValidateInput()
        {
            if (String::IsNullOrEmpty(txtFirstName->Text) ||
                String::IsNullOrEmpty(txtLastName->Text) ||
                String::IsNullOrEmpty(txtEmail->Text) ||
                String::IsNullOrEmpty(txtUsername->Text) ||
                String::IsNullOrEmpty(txtPassword->Text) ||
                String::IsNullOrEmpty(txtConfirmPassword->Text) ||
                cmbRole->SelectedIndex == -1) {
                MessageBox::Show("Please fill in all required fields.");
                return false;
            }

            if (txtPassword->Text != txtConfirmPassword->Text) {
                MessageBox::Show("Passwords do not match.");
                return false;
            }

            // Role-specific validation
            if (cmbRole->SelectedIndex == 0) { // Student
                if (String::IsNullOrEmpty(txtBatch->Text) || cmbProgram->SelectedIndex == -1) {
                    MessageBox::Show("Please fill in all student-specific fields.");
                    return false;
                }
            }
            else if (cmbRole->SelectedIndex == 1) { // Faculty
                if (cmbDepartment->SelectedIndex == -1 || String::IsNullOrEmpty(txtSpecialization->Text)) {
                    MessageBox::Show("Please fill in all faculty-specific fields.");
                    return false;
                }
            }

            return true;
        }

        void btnSignUp_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (!ValidateInput()) return;

            try {
                if (sqlConnection->State == ConnectionState::Closed) {
                    sqlConnection->Open();
                }

                MySqlTransaction^ transaction = sqlConnection->BeginTransaction();

                try {
                    // Insert into USER table
                    String^ userQuery = "INSERT INTO USER (userID, firstName, lastName, email, password, roleID, username, dateCreated, lastModified, isActive) VALUES (@userID, @firstName, @lastName, @email, @password, @roleID, @username, NOW(), NOW(), true)";

                    String^ userID;
                    int roleID;

                    if (cmbRole->SelectedIndex == 0) { // Student
                        userID = "STU" + DateTime::Now.ToString("yyyyMMddHHmmss");
                        roleID = 3; // Student role ID
                    }
                    else { // Faculty
                        userID = "FAC" + DateTime::Now.ToString("yyyyMMddHHmmss");
                        roleID = 2; // Faculty role ID
                    }

                    MySqlCommand^ userCmd = gcnew MySqlCommand(userQuery, sqlConnection);
                    userCmd->Transaction = transaction;
                    userCmd->Parameters->AddWithValue("@userID", userID);
                    userCmd->Parameters->AddWithValue("@firstName", txtFirstName->Text);
                    userCmd->Parameters->AddWithValue("@lastName", txtLastName->Text);
                    userCmd->Parameters->AddWithValue("@email", txtEmail->Text);
                    userCmd->Parameters->AddWithValue("@password", txtPassword->Text);
                    userCmd->Parameters->AddWithValue("@roleID", roleID);
                    userCmd->Parameters->AddWithValue("@username", txtUsername->Text);
                    userCmd->ExecuteNonQuery();

                    if (cmbRole->SelectedIndex == 0) { // Student
                        String^ studentQuery = "INSERT INTO STUDENT (userID, studentID, programCode, batch) VALUES (@userID, @studentID, @programCode, @batch)";

                        MySqlCommand^ studentCmd = gcnew MySqlCommand(studentQuery, sqlConnection);
                        studentCmd->Transaction = transaction;
                        studentCmd->Parameters->AddWithValue("@userID", userID);
                        studentCmd->Parameters->AddWithValue("@studentID", userID);
                        studentCmd->Parameters->AddWithValue("@programCode", cmbProgram->SelectedValue);
                        studentCmd->Parameters->AddWithValue("@batch", txtBatch->Text);
                        studentCmd->ExecuteNonQuery();
                    }
                    else { // Faculty
                        String^ facultyQuery = "INSERT INTO FACULTY (userID, departmentCode, specialization, dateOfAppointment) VALUES (@userID, @departmentCode, @specialization, CURDATE())";

                        MySqlCommand^ facultyCmd = gcnew MySqlCommand(facultyQuery, sqlConnection);
                        facultyCmd->Transaction = transaction;
                        facultyCmd->Parameters->AddWithValue("@userID", userID);
                        facultyCmd->Parameters->AddWithValue("@departmentCode", cmbDepartment->SelectedValue);
                        facultyCmd->Parameters->AddWithValue("@specialization", txtSpecialization->Text);
                        facultyCmd->ExecuteNonQuery();
                    }

                    transaction->Commit();
                    MessageBox::Show("Account created successfully!");
                    this->Hide();
                    logForm->ShowDialog();
                }
                catch (Exception^ ex) {
                    transaction->Rollback();
                    throw ex;
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error creating account: " + ex->Message);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open) {
                    sqlConnection->Close();
                }
            }
        }

        void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
        {
            this->Close();
        }

        void lnkLogin_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
        {
            this->Hide();
            logForm->ShowDialog();
        }
    };
}