#pragma once
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    public ref class UserManagementForm : public System::Windows::Forms::Form
    {
    public:
        UserManagementForm(void)
        {
            InitializeComponent();
            LoadUsers();
            LoadRoles();
        }

    protected:
        ~UserManagementForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        // Form controls
        System::Windows::Forms::DataGridView^ dgvUsers;
        System::Windows::Forms::TextBox^ txtUserID;
        System::Windows::Forms::TextBox^ txtFirstName;
        System::Windows::Forms::TextBox^ txtLastName;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::TextBox^ txtUsername;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::ComboBox^ cboRole;
        System::Windows::Forms::CheckBox^ chkActive;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnClear;
        System::Windows::Forms::GroupBox^ grpUserDetails;
        System::Windows::Forms::Label^ lblUserID;
        System::Windows::Forms::Label^ lblFirstName;
        System::Windows::Forms::Label^ lblLastName;
        System::Windows::Forms::Label^ lblEmail;
        System::Windows::Forms::Label^ lblUsername;
        System::Windows::Forms::Label^ lblPassword;
        System::Windows::Forms::Label^ lblRole;

        System::ComponentModel::Container^ components;
        String^ connectionString = "Server=localhost;Database=university_system;Uid=aseda;Pwd=FatherAbraham2";

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Text = L"User Management";
            this->Size = System::Drawing::Size(1000, 600);

            // Initialize DataGridView
            this->dgvUsers = gcnew DataGridView();
            this->dgvUsers->Location = System::Drawing::Point(20, 20);
            this->dgvUsers->Size = System::Drawing::Size(600, 400);
            this->dgvUsers->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvUsers->MultiSelect = false;
            this->dgvUsers->AllowUserToAddRows = false;
            this->dgvUsers->ReadOnly = true;
            this->dgvUsers->SelectionChanged += gcnew EventHandler(this, &UserManagementForm::dgvUsers_SelectionChanged);

            // Initialize GroupBox
            this->grpUserDetails = gcnew GroupBox();
            this->grpUserDetails->Text = L"User Details";
            this->grpUserDetails->Location = System::Drawing::Point(640, 20);
            this->grpUserDetails->Size = System::Drawing::Size(320, 500);

            // Labels
            this->lblUserID = gcnew Label();
            this->lblUserID->Text = L"User ID:";
            this->lblUserID->Location = System::Drawing::Point(20, 30);
            this->lblUserID->AutoSize = true;

            this->lblFirstName = gcnew Label();
            this->lblFirstName->Text = L"First Name:";
            this->lblFirstName->Location = System::Drawing::Point(20, 70);
            this->lblFirstName->AutoSize = true;

            this->lblLastName = gcnew Label();
            this->lblLastName->Text = L"Last Name:";
            this->lblLastName->Location = System::Drawing::Point(20, 110);
            this->lblLastName->AutoSize = true;

            this->lblEmail = gcnew Label();
            this->lblEmail->Text = L"Email:";
            this->lblEmail->Location = System::Drawing::Point(20, 150);
            this->lblEmail->AutoSize = true;

            this->lblUsername = gcnew Label();
            this->lblUsername->Text = L"Username:";
            this->lblUsername->Location = System::Drawing::Point(20, 190);
            this->lblUsername->AutoSize = true;

            this->lblPassword = gcnew Label();
            this->lblPassword->Text = L"Password:";
            this->lblPassword->Location = System::Drawing::Point(20, 230);
            this->lblPassword->AutoSize = true;

            this->lblRole = gcnew Label();
            this->lblRole->Text = L"Role:";
            this->lblRole->Location = System::Drawing::Point(20, 270);
            this->lblRole->AutoSize = true;

            // TextBoxes and Controls
            this->txtUserID = gcnew TextBox();
            this->txtUserID->Location = System::Drawing::Point(120, 30);
            this->txtUserID->Size = System::Drawing::Size(180, 20);
            this->txtUserID->ReadOnly = true;

            this->txtFirstName = gcnew TextBox();
            this->txtFirstName->Location = System::Drawing::Point(120, 70);
            this->txtFirstName->Size = System::Drawing::Size(180, 20);

            this->txtLastName = gcnew TextBox();
            this->txtLastName->Location = System::Drawing::Point(120, 110);
            this->txtLastName->Size = System::Drawing::Size(180, 20);

            this->txtEmail = gcnew TextBox();
            this->txtEmail->Location = System::Drawing::Point(120, 150);
            this->txtEmail->Size = System::Drawing::Size(180, 20);

            this->txtUsername = gcnew TextBox();
            this->txtUsername->Location = System::Drawing::Point(120, 190);
            this->txtUsername->Size = System::Drawing::Size(180, 20);

            this->txtPassword = gcnew TextBox();
            this->txtPassword->Location = System::Drawing::Point(120, 230);
            this->txtPassword->Size = System::Drawing::Size(180, 20);
            this->txtPassword->PasswordChar = '*';

            this->cboRole = gcnew ComboBox();
            this->cboRole->Location = System::Drawing::Point(120, 270);
            this->cboRole->Size = System::Drawing::Size(180, 20);
            this->cboRole->DropDownStyle = ComboBoxStyle::DropDownList;

            this->chkActive = gcnew CheckBox();
            this->chkActive->Text = L"Active";
            this->chkActive->Location = System::Drawing::Point(120, 310);
            this->chkActive->Checked = true;

            // Buttons
            this->btnAdd = gcnew Button();
            this->btnAdd->Text = L"Add User";
            this->btnAdd->Location = System::Drawing::Point(20, 350);
            this->btnAdd->Size = System::Drawing::Size(100, 30);
            this->btnAdd->Click += gcnew EventHandler(this, &UserManagementForm::btnAdd_Click);

            this->btnUpdate = gcnew Button();
            this->btnUpdate->Text = L"Update";
            this->btnUpdate->Location = System::Drawing::Point(130, 350);
            this->btnUpdate->Size = System::Drawing::Size(100, 30);
            this->btnUpdate->Click += gcnew EventHandler(this, &UserManagementForm::btnUpdate_Click);

            this->btnDelete = gcnew Button();
            this->btnDelete->Text = L"Delete";
            this->btnDelete->Location = System::Drawing::Point(20, 390);
            this->btnDelete->Size = System::Drawing::Size(100, 30);
            this->btnDelete->Click += gcnew EventHandler(this, &UserManagementForm::btnDelete_Click);

            this->btnClear = gcnew Button();
            this->btnClear->Text = L"Clear";
            this->btnClear->Location = System::Drawing::Point(130, 390);
            this->btnClear->Size = System::Drawing::Size(100, 30);
            this->btnClear->Click += gcnew EventHandler(this, &UserManagementForm::btnClear_Click);

            // Add controls to GroupBox
            this->grpUserDetails->Controls->AddRange(gcnew array<Control^> {
                this->lblUserID, this->lblFirstName, this->lblLastName, this->lblEmail,
                    this->lblUsername, this->lblPassword, this->lblRole,
                    this->txtUserID, this->txtFirstName, this->txtLastName, this->txtEmail,
                    this->txtUsername, this->txtPassword, this->cboRole, this->chkActive,
                    this->btnAdd, this->btnUpdate, this->btnDelete, this->btnClear
            });

            // Add controls to form
            this->Controls->Add(this->dgvUsers);
            this->Controls->Add(this->grpUserDetails);
        }

        void LoadUsers()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(
                    "SELECT u.userID, u.firstName, u.lastName, u.email, u.username, "
                    "r.roleName, u.isActive "
                    "FROM user u "
                    "JOIN user_role r ON u.roleID = r.id "
                    "ORDER BY u.lastName, u.firstName", conn);

                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);
                dgvUsers->DataSource = dt;

                // Configure columns
                dgvUsers->Columns["userID"]->HeaderText = "User ID";
                dgvUsers->Columns["firstName"]->HeaderText = "First Name";
                dgvUsers->Columns["lastName"]->HeaderText = "Last Name";
                dgvUsers->Columns["email"]->HeaderText = "Email";
                dgvUsers->Columns["username"]->HeaderText = "Username";
                dgvUsers->Columns["roleName"]->HeaderText = "Role";
                dgvUsers->Columns["isActive"]->HeaderText = "Active";
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading users: " + ex->Message);
            }
        }

        void LoadRoles()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand("SELECT id, roleName FROM user_role", conn);
                conn->Open();

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);

                cboRole->DisplayMember = "roleName";
                cboRole->ValueMember = "id";
                cboRole->DataSource = dt;

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading roles: " + ex->Message);
            }
        }

        void ClearInputs()
        {
            txtUserID->Clear();
            txtFirstName->Clear();
            txtLastName->Clear();
            txtEmail->Clear();
            txtUsername->Clear();
            txtPassword->Clear();
            cboRole->SelectedIndex = -1;
            chkActive->Checked = true;
        }

        bool ValidateInputs()
        {
            if (String::IsNullOrEmpty(txtFirstName->Text->Trim())) {
                MessageBox::Show("Please enter First Name");
                return false;
            }
            if (String::IsNullOrEmpty(txtLastName->Text->Trim())) {
                MessageBox::Show("Please enter Last Name");
                return false;
            }
            if (String::IsNullOrEmpty(txtEmail->Text->Trim())) {
                MessageBox::Show("Please enter Email");
                return false;
            }
            if (String::IsNullOrEmpty(txtUsername->Text->Trim())) {
                MessageBox::Show("Please enter Username");
                return false;
            }
            if (String::IsNullOrEmpty(txtPassword->Text)) {
                MessageBox::Show("Please enter Password");
                return false;
            }
            if (cboRole->SelectedValue == nullptr) {
                MessageBox::Show("Please select Role");
                return false;
            }
            return true;
        }

        void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (!ValidateInputs()) return;

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "INSERT INTO user (userID, firstName, lastName, email, username, password, roleID, isActive) "
                    "VALUES (@userID, @firstName, @lastName, @email, @username, @password, @roleID, @isActive)", conn);

                String^ newUserID = GenerateUserID();
                cmd->Parameters->AddWithValue("@userID", newUserID);
                cmd->Parameters->AddWithValue("@firstName", txtFirstName->Text->Trim());
                cmd->Parameters->AddWithValue("@lastName", txtLastName->Text->Trim());
                cmd->Parameters->AddWithValue("@email", txtEmail->Text->Trim());
                cmd->Parameters->AddWithValue("@username", txtUsername->Text->Trim());
                cmd->Parameters->AddWithValue("@password", txtPassword->Text);
                cmd->Parameters->AddWithValue("@roleID", cboRole->SelectedValue);
                cmd->Parameters->AddWithValue("@isActive", chkActive->Checked);

                conn->Open();
                cmd->ExecuteNonQuery();
                MessageBox::Show("User added successfully!");

                ClearInputs();
                LoadUsers();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error adding user: " + ex->Message);
            }
        }

        String^ GenerateUserID()
        {
            String^ prefix;
            if (cboRole->Text == "STUDENT")
                prefix = "STU";
            else if (cboRole->Text == "FACULTY")
                prefix = "FAC";
            else if (cboRole->Text == "ADMIN")
                prefix = "ADM";
            else
                prefix = "USR";

            return prefix + DateTime::Now.ToString("yyyyMMddHHmmss");
        }

        void dgvUsers_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (dgvUsers->SelectedRows->Count > 0) {
                DataGridViewRow^ row = dgvUsers->SelectedRows[0];
                txtUserID->Text = row->Cells["userID"]->Value->ToString();
                txtFirstName->Text = row->Cells["firstName"]->Value->ToString();
                txtLastName->Text = row->Cells["lastName"]->Value->ToString();
                txtEmail->Text = row->Cells["email"]->Value->ToString();
                txtUsername->Text = row->Cells["username"]->Value->ToString();
                cboRole->Text = row->Cells["roleName"]->Value->ToString();
                chkActive->Checked = Convert::ToBoolean(row->Cells["isActive"]->Value);
                txtPassword->Clear(); // Don't show password
            }
        }

        void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (String::IsNullOrEmpty(txtUserID->Text)) {
                MessageBox::Show("Please select a user to update.");
                return;
            }

            if (!ValidateInputs()) return;

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                String^ query = "UPDATE user SET firstName = @firstName, lastName = @lastName, "
                    "email = @email, username = @username, roleID = @roleID, isActive = @isActive";

                // Only update password if a new one is provided
                if (!String::IsNullOrEmpty(txtPassword->Text)) {
                    query += ", password = @password";
                }

                query += " WHERE userID = @userID";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@firstName", txtFirstName->Text->Trim());
                cmd->Parameters->AddWithValue("@lastName", txtLastName->Text->Trim());
                cmd->Parameters->AddWithValue("@email", txtEmail->Text->Trim());
                cmd->Parameters->AddWithValue("@username", txtUsername->Text->Trim());
                cmd->Parameters->AddWithValue("@roleID", cboRole->SelectedValue);
                cmd->Parameters->AddWithValue("@isActive", chkActive->Checked);
                cmd->Parameters->AddWithValue("@userID", txtUserID->Text);

                if (!String::IsNullOrEmpty(txtPassword->Text)) {
                    cmd->Parameters->AddWithValue("@password", txtPassword->Text);
                }

                conn->Open();
                int rowsAffected = cmd->ExecuteNonQuery();
                if (rowsAffected > 0) {
                    MessageBox::Show("User updated successfully!");
                    LoadUsers();
                }
                else {
                    MessageBox::Show("User not found.");
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error updating user: " + ex->Message);
            }
        }

        void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (String::IsNullOrEmpty(txtUserID->Text)) {
                MessageBox::Show("Please select a user to delete.");
                return;
            }

            if (MessageBox::Show("Are you sure you want to deactivate this user?",
                "Confirm Deactivation", MessageBoxButtons::YesNo,
                MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::No) {
                return;
            }

            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                // Soft delete - just set isActive to false
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "UPDATE user SET isActive = 0 WHERE userID = @userID", conn);
                cmd->Parameters->AddWithValue("@userID", txtUserID->Text);

                conn->Open();
                int rowsAffected = cmd->ExecuteNonQuery();
                if (rowsAffected > 0) {
                    MessageBox::Show("User deactivated successfully!");
                    ClearInputs();
                    LoadUsers();
                }
                else {
                    MessageBox::Show("User not found.");
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error deactivating user: " + ex->Message);
            }
        }

        void btnClear_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ClearInputs();
            dgvUsers->ClearSelection();
        }

        bool IsEmailValid(String^ email) {
            try {
                System::Net::Mail::MailAddress^ addr = gcnew System::Net::Mail::MailAddress(email);
                return addr->Address == email;
            }
            catch (...) {
                return false;
            }
        }
    };
}