#pragma once
#include "MDI.h"
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        // Public property to store authenticated user's role and ID
        property String^ UserRole;
        property String^ UserID;

    private:
        // Form components
        System::Windows::Forms::Panel^ mainPanel;
        System::Windows::Forms::Panel^ headerPanel;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblSubtitle;
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Button^ btnLogin;
        System::Windows::Forms::Button^ btnExit;
        System::Windows::Forms::Label^ lblUsername;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::PictureBox^ logoBox;
        System::Windows::Forms::LinkLabel^ lnkForgotPassword;
        System::ComponentModel::Container^ components;

        // Database connection
        MySqlConnection^ sqlConnection;
        String^ connectString = "server=localhost;port=3306;database=university_system;uid=aseda;password=FatherAbraham2";

    public:
        LoginForm(void)
        {
            InitializeComponent();
            ConfigureDatabase();
        }

    protected:
        ~LoginForm()
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

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // Form Configuration
            this->Text = L"University Management System - Login";
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Size = System::Drawing::Size(450, 600);
            this->BackColor = System::Drawing::Color::White;

            // Header Panel
            this->headerPanel = gcnew System::Windows::Forms::Panel();
            this->headerPanel->BackColor = System::Drawing::Color::FromArgb(0, 71, 160);
            this->headerPanel->Dock = System::Windows::Forms::DockStyle::Top;
            this->headerPanel->Height = 100;

            // Title Label
            this->lblTitle = gcnew System::Windows::Forms::Label();
            this->lblTitle->Text = L"University Management System";
            this->lblTitle->Font = gcnew System::Drawing::Font("Arial", 20, FontStyle::Bold);
            this->lblTitle->ForeColor = System::Drawing::Color::White;
            this->lblTitle->AutoSize = false;
            this->lblTitle->Size = System::Drawing::Size(450, 40);
            this->lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            this->lblTitle->Location = Point(0, 30);
            this->headerPanel->Controls->Add(this->lblTitle);

            // Main Panel
            this->mainPanel = gcnew System::Windows::Forms::Panel();
            this->mainPanel->Dock = System::Windows::Forms::DockStyle::Fill;
            this->mainPanel->Padding = System::Windows::Forms::Padding(40);

            // Username Label and TextBox
            this->lblUsername = gcnew System::Windows::Forms::Label();
            this->lblUsername->Text = L"Username";
            this->lblUsername->Font = gcnew System::Drawing::Font("Arial", 12);
            this->lblUsername->Location = Point(75, 250);
            this->lblUsername->AutoSize = true;

            this->txtUsername = gcnew System::Windows::Forms::TextBox();
            this->txtUsername->Location = Point(75, 275);
            this->txtUsername->Size = System::Drawing::Size(300, 25);
            this->txtUsername->Font = gcnew System::Drawing::Font("Arial", 12);

            // Password Label and TextBox
            this->lblPassword = gcnew System::Windows::Forms::Label();
            this->lblPassword->Text = L"Password";
            this->lblPassword->Font = gcnew System::Drawing::Font("Arial", 12);
            this->lblPassword->Location = Point(75, 315);
            this->lblPassword->AutoSize = true;

            this->txtPassword = gcnew System::Windows::Forms::TextBox();
            this->txtPassword->Location = Point(75, 340);
            this->txtPassword->Size = System::Drawing::Size(300, 25);
            this->txtPassword->Font = gcnew System::Drawing::Font("Arial", 12);
            this->txtPassword->PasswordChar = '•';

            // Forgot Password Link
            this->lnkForgotPassword = gcnew System::Windows::Forms::LinkLabel();
            this->lnkForgotPassword->Text = L"Forgot Password?";
            this->lnkForgotPassword->Location = Point(75, 370);
            this->lnkForgotPassword->AutoSize = true;
            this->lnkForgotPassword->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(
                this, &LoginForm::lnkForgotPassword_LinkClicked);

            // Login Button
            this->btnLogin = gcnew System::Windows::Forms::Button();
            this->btnLogin->Text = L"Login";
            this->btnLogin->Location = Point(75, 410);
            this->btnLogin->Size = System::Drawing::Size(300, 40);
            this->btnLogin->BackColor = System::Drawing::Color::FromArgb(0, 71, 160);
            this->btnLogin->ForeColor = System::Drawing::Color::White;
            this->btnLogin->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnLogin->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
            this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);

            // Exit Button
            this->btnExit = gcnew System::Windows::Forms::Button();
            this->btnExit->Text = L"Exit";
            this->btnExit->Location = Point(75, 460);
            this->btnExit->Size = System::Drawing::Size(300, 40);
            this->btnExit->BackColor = System::Drawing::Color::White;
            this->btnExit->ForeColor = System::Drawing::Color::FromArgb(0, 71, 160);
            this->btnExit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
            this->btnExit->Font = gcnew System::Drawing::Font("Arial", 12);
            this->btnExit->Click += gcnew System::EventHandler(this, &LoginForm::btnExit_Click);

            // Add controls to form
            this->Controls->Add(this->headerPanel);
            this->Controls->Add(this->lblUsername);
            this->Controls->Add(this->txtUsername);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->lnkForgotPassword);
            this->Controls->Add(this->btnLogin);
            this->Controls->Add(this->btnExit);  

            // Set accept button
            this->AcceptButton = this->btnLogin;
        }

        void btnLogin_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (String::IsNullOrEmpty(txtUsername->Text) || String::IsNullOrEmpty(txtPassword->Text)) {
                MessageBox::Show("Please enter both username and password.",
                    "Login Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            try {
                if (sqlConnection->State == ConnectionState::Closed) {
                    sqlConnection->Open();
                }

                String^ query = "SELECT u.userID, r.roleName FROM USER u "
                    "INNER JOIN USER_ROLE r ON u.roleID = r.id "
                    "WHERE u.username = @username AND u.password = @password "
                    "AND u.isActive = true";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                cmd->Parameters->AddWithValue("@username", txtUsername->Text);
                cmd->Parameters->AddWithValue("@password", txtPassword->Text); // In production, use proper hashing

                MySqlDataReader^ reader = cmd->ExecuteReader();

                if (reader->Read()) {
                    this->UserID = reader["userID"]->ToString();
                    this->UserRole = reader["roleName"]->ToString();

                    this->DialogResult = System::Windows::Forms::DialogResult::OK;
                    MessageBox::Show("Logged in successfully",
                        "Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);

                    this->Hide();
                    MainMDIForm^ mdiForm = gcnew MainMDIForm(this->UserID, this->UserRole);
                    mdiForm->ShowDialog();
                }
                else {
                    MessageBox::Show("Invalid username or password.",
                        "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Login error: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open) {
                    sqlConnection->Close();
                }
            }
        }

        void btnExit_Click(System::Object^ sender, System::EventArgs^ e)
        {
            Application::Exit();
        }

        void lnkForgotPassword_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
        {
            MessageBox::Show("Please contact your system administrator to reset your password.",
                "Password Reset", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    };
}