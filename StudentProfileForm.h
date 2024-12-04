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
    using namespace System::IO;

    public ref class StudentProfileForm : public System::Windows::Forms::Form {
    public:
        StudentProfileForm(String^ studentID) {
            InitializeComponent();
            this->studentID = studentID;
            LoadStudentProfile();
        }

    protected:
        ~StudentProfileForm() {
            if (components) {
                delete components;
            }
        }

    private:
        String^ studentID;
        String^ connectionString = "Server=localhost;Database=university_system;Uid=aseda;Pwd=FatherAbraham2";

        // Form controls
        System::Windows::Forms::GroupBox^ grpPersonalInfo;
        System::Windows::Forms::GroupBox^ grpAcademicInfo;

        System::Windows::Forms::Label^ lblStudentID;
        System::Windows::Forms::TextBox^ txtStudentID;
        System::Windows::Forms::Label^ lblFirstName;
        System::Windows::Forms::TextBox^ txtFirstName;
        System::Windows::Forms::Label^ lblLastName;
        System::Windows::Forms::TextBox^ txtLastName;
        System::Windows::Forms::Label^ lblEmail;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::Label^ lblProgram;
        System::Windows::Forms::ComboBox^ cboProgram;
        System::Windows::Forms::Label^ lblBatch;
        System::Windows::Forms::TextBox^ txtBatch;
        System::Windows::Forms::Label^ lblAdmissionDate;
        System::Windows::Forms::DateTimePicker^ dtpAdmissionDate;
        System::Windows::Forms::Label^ lblExpectedGradDate;
        System::Windows::Forms::DateTimePicker^ dtpExpectedGradDate;

        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Button^ btnCancel;
        System::Windows::Forms::PictureBox^ pictureBox;
        System::Windows::Forms::Button^ btnUploadPhoto;

        System::ComponentModel::Container^ components;

        void InitializeComponent(void) {
            this->Text = "Student Profile";
            this->Size = System::Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;

            // Initialize Personal Info Group Box
            this->grpPersonalInfo = gcnew GroupBox();
            this->grpPersonalInfo->Text = "Personal Information";
            this->grpPersonalInfo->Location = System::Drawing::Point(20, 20);
            this->grpPersonalInfo->Size = System::Drawing::Size(350, 400);

            // Student ID
            this->lblStudentID = gcnew Label();
            this->lblStudentID->Text = "Student ID:";
            this->lblStudentID->Location = System::Drawing::Point(20, 30);
            this->lblStudentID->AutoSize = true;

            this->txtStudentID = gcnew TextBox();
            this->txtStudentID->Location = System::Drawing::Point(120, 30);
            this->txtStudentID->Size = System::Drawing::Size(200, 20);
            this->txtStudentID->ReadOnly = true;

            // First Name
            this->lblFirstName = gcnew Label();
            this->lblFirstName->Text = "First Name:";
            this->lblFirstName->Location = System::Drawing::Point(20, 70);
            this->lblFirstName->AutoSize = true;

            this->txtFirstName = gcnew TextBox();
            this->txtFirstName->Location = System::Drawing::Point(120, 70);
            this->txtFirstName->Size = System::Drawing::Size(200, 20);

            // Last Name
            this->lblLastName = gcnew Label();
            this->lblLastName->Text = "Last Name:";
            this->lblLastName->Location = System::Drawing::Point(20, 110);
            this->lblLastName->AutoSize = true;

            this->txtLastName = gcnew TextBox();
            this->txtLastName->Location = System::Drawing::Point(120, 110);
            this->txtLastName->Size = System::Drawing::Size(200, 20);

            // Email
            this->lblEmail = gcnew Label();
            this->lblEmail->Text = "Email:";
            this->lblEmail->Location = System::Drawing::Point(20, 150);
            this->lblEmail->AutoSize = true;

            this->txtEmail = gcnew TextBox();
            this->txtEmail->Location = System::Drawing::Point(120, 150);
            this->txtEmail->Size = System::Drawing::Size(200, 20);

            // Picture Box for Photo
            this->pictureBox = gcnew PictureBox();
            this->pictureBox->Location = System::Drawing::Point(120, 190);
            this->pictureBox->Size = System::Drawing::Size(150, 150);
            this->pictureBox->SizeMode = PictureBoxSizeMode::StretchImage;
            this->pictureBox->BorderStyle = BorderStyle::FixedSingle;

            // Upload Photo Button
            this->btnUploadPhoto = gcnew Button();
            this->btnUploadPhoto->Text = "Upload Photo";
            this->btnUploadPhoto->Location = System::Drawing::Point(120, 350);
            this->btnUploadPhoto->Size = System::Drawing::Size(150, 30);
            this->btnUploadPhoto->Click += gcnew EventHandler(this, &StudentProfileForm::btnUploadPhoto_Click);

            // Initialize Academic Info Group Box
            this->grpAcademicInfo = gcnew GroupBox();
            this->grpAcademicInfo->Text = "Academic Information";
            this->grpAcademicInfo->Location = System::Drawing::Point(390, 20);
            this->grpAcademicInfo->Size = System::Drawing::Size(370, 400);

            // Program
            this->lblProgram = gcnew Label();
            this->lblProgram->Text = "Program:";
            this->lblProgram->Location = System::Drawing::Point(20, 30);
            this->lblProgram->AutoSize = true;

            this->cboProgram = gcnew ComboBox();
            this->cboProgram->Location = System::Drawing::Point(120, 30);
            this->cboProgram->Size = System::Drawing::Size(230, 20);
            this->cboProgram->DropDownStyle = ComboBoxStyle::DropDownList;

            // Batch
            this->lblBatch = gcnew Label();
            this->lblBatch->Text = "Batch:";
            this->lblBatch->Location = System::Drawing::Point(20, 70);
            this->lblBatch->AutoSize = true;

            this->txtBatch = gcnew TextBox();
            this->txtBatch->Location = System::Drawing::Point(120, 70);
            this->txtBatch->Size = System::Drawing::Size(100, 20);

            // Admission Date
            this->lblAdmissionDate = gcnew Label();
            this->lblAdmissionDate->Text = "Admission Date:";
            this->lblAdmissionDate->Location = System::Drawing::Point(20, 110);
            this->lblAdmissionDate->AutoSize = true;

            this->dtpAdmissionDate = gcnew DateTimePicker();
            this->dtpAdmissionDate->Location = System::Drawing::Point(120, 110);
            this->dtpAdmissionDate->Size = System::Drawing::Size(200, 20);
            this->dtpAdmissionDate->Format = DateTimePickerFormat::Short;

            // Expected Graduation Date
            this->lblExpectedGradDate = gcnew Label();
            this->lblExpectedGradDate->Text = "Expected Graduation:";
            this->lblExpectedGradDate->Location = System::Drawing::Point(20, 150);
            this->lblExpectedGradDate->AutoSize = true;

            this->dtpExpectedGradDate = gcnew DateTimePicker();
            this->dtpExpectedGradDate->Location = System::Drawing::Point(120, 150);
            this->dtpExpectedGradDate->Size = System::Drawing::Size(200, 20);
            this->dtpExpectedGradDate->Format = DateTimePickerFormat::Short;

            // Update Button
            this->btnUpdate = gcnew Button();
            this->btnUpdate->Text = "Update Profile";
            this->btnUpdate->Location = System::Drawing::Point(390, 440);
            this->btnUpdate->Size = System::Drawing::Size(180, 35);
            this->btnUpdate->Click += gcnew EventHandler(this, &StudentProfileForm::btnUpdate_Click);

            // Cancel Button
            this->btnCancel = gcnew Button();
            this->btnCancel->Text = "Cancel";
            this->btnCancel->Location = System::Drawing::Point(580, 440);
            this->btnCancel->Size = System::Drawing::Size(180, 35);
            this->btnCancel->Click += gcnew EventHandler(this, &StudentProfileForm::btnCancel_Click);

            // Add controls to group boxes
            this->grpPersonalInfo->Controls->AddRange(gcnew array<Control^> {
                this->lblStudentID, this->txtStudentID,
                    this->lblFirstName, this->txtFirstName,
                    this->lblLastName, this->txtLastName,
                    this->lblEmail, this->txtEmail,
                    this->pictureBox, this->btnUploadPhoto
            });

            this->grpAcademicInfo->Controls->AddRange(gcnew array<Control^> {
                this->lblProgram, this->cboProgram,
                    this->lblBatch, this->txtBatch,
                    this->lblAdmissionDate, this->dtpAdmissionDate,
                    this->lblExpectedGradDate, this->dtpExpectedGradDate
            });

            // Add group boxes and buttons to form
            this->Controls->Add(this->grpPersonalInfo);
            this->Controls->Add(this->grpAcademicInfo);
            this->Controls->Add(this->btnUpdate);
            this->Controls->Add(this->btnCancel);

            // Load initial data
            LoadPrograms();
        }

        void LoadPrograms() {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "SELECT programCode, programName FROM academic_program WHERE isActive = 1", conn);

                conn->Open();
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);

                cboProgram->DisplayMember = "programName";
                cboProgram->ValueMember = "programCode";
                cboProgram->DataSource = dt;

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading programs: " + ex->Message);
            }
        }

        void LoadStudentProfile() {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                String^ query = "SELECT s.*, u.firstName, u.lastName, u.email "
                    "FROM student s "
                    "JOIN user u ON s.userID = u.userID "
                    "WHERE s.studentID = @studentID";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@studentID", studentID);

                conn->Open();
                MySqlDataReader^ reader = cmd->ExecuteReader();

                if (reader->Read()) {
                    txtStudentID->Text = reader["studentID"]->ToString();
                    txtFirstName->Text = reader["firstName"]->ToString();
                    txtLastName->Text = reader["lastName"]->ToString();
                    txtEmail->Text = reader["email"]->ToString();
                    cboProgram->SelectedValue = reader["programCode"]->ToString();
                    txtBatch->Text = reader["batch"]->ToString();

                    if (!reader->IsDBNull(reader->GetOrdinal("admissionDate")))
                        dtpAdmissionDate->Value = Convert::ToDateTime(reader["admissionDate"]);

                    if (!reader->IsDBNull(reader->GetOrdinal("expectedGraduationDate")))
                        dtpExpectedGradDate->Value = Convert::ToDateTime(reader["expectedGraduationDate"]);
                }

                reader->Close();
                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading student profile: " + ex->Message);
            }
        }

        void btnUploadPhoto_Click(System::Object^ sender, System::EventArgs^ e) {
            OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
            openFileDialog->Filter = "Image Files (*.jpg; *.jpeg; *.png; *.gif; *.bmp)|*.jpg;*.jpeg;*.png;*.gif;*.bmp";

            if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                try {
                    pictureBox->Image = Image::FromFile(openFileDialog->FileName);
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Error loading image: " + ex->Message);
                }
            }
        }

        void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e) {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                conn->Open();

                // Start transaction
                MySqlTransaction^ transaction = conn->BeginTransaction();

                try {
                    // Update user table
                    String^ updateUserQuery = "UPDATE user SET firstName = @firstName, lastName = @lastName, "
                        "email = @email WHERE userID = (SELECT userID FROM student WHERE studentID = @studentID)";

                    MySqlCommand^ userCmd = gcnew MySqlCommand(updateUserQuery, conn);
                    userCmd->Transaction = transaction;
                    userCmd->Parameters->AddWithValue("@firstName", txtFirstName->Text);
                    userCmd->Parameters->AddWithValue("@lastName", txtLastName->Text);
                    userCmd->Parameters->AddWithValue("@email", txtEmail->Text);
                    userCmd->Parameters->AddWithValue("@studentID", studentID);
                    userCmd->ExecuteNonQuery();

                    // Update student table
                    String^ updateStudentQuery = "UPDATE student SET programCode = @programCode, "
                        "batch = @batch, admissionDate = @admissionDate, "
                        "expectedGraduationDate = @expectedGradDate "
                        "WHERE studentID = @studentID";

                    MySqlCommand^ studentCmd = gcnew MySqlCommand(updateStudentQuery, conn);
                    studentCmd->Transaction = transaction;
                    studentCmd->Parameters->AddWithValue("@programCode", cboProgram->SelectedValue->ToString());
                    studentCmd->Parameters->AddWithValue("@batch", txtBatch->Text);
                    studentCmd->Parameters->AddWithValue("@admissionDate", dtpAdmissionDate->Value);
                    studentCmd->Parameters->AddWithValue("@expectedGradDate", dtpExpectedGradDate->Value);
                    studentCmd->Parameters->AddWithValue("@studentID", studentID);
                    studentCmd->ExecuteNonQuery();

                    // Commit transaction
                    transaction->Commit();
                    MessageBox::Show("Profile updated successfully!");
                }
                catch (Exception^ ex) {
                    // Rollback transaction if there's an error
                    transaction->Rollback();
                    throw ex;
                }

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error updating profile: " + ex->Message);
            }
        }

        void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
            this->Close();
        }

        // Validation methods
        bool ValidateInput() {
            // Check required fields
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

            if (String::IsNullOrEmpty(txtBatch->Text->Trim())) {
                MessageBox::Show("Please enter Batch");
                return false;
            }

            // Validate email format
            if (!IsValidEmail(txtEmail->Text->Trim())) {
                MessageBox::Show("Please enter a valid email address");
                return false;
            }

            // Validate dates
            if (dtpAdmissionDate->Value > dtpExpectedGradDate->Value) {
                MessageBox::Show("Admission date cannot be later than expected graduation date");
                return false;
            }

            // Validate batch format (assuming it should be a year)
            if (!IsValidBatch(txtBatch->Text->Trim())) {
                MessageBox::Show("Batch should be a valid year format (e.g., 2024)");
                return false;
            }

            return true;
        }

        bool IsValidEmail(String^ email) {
            try {
                System::Text::RegularExpressions::Regex^ regex =
                    gcnew System::Text::RegularExpressions::Regex(
                        "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
                return regex->IsMatch(email);
            }
            catch (Exception^) {
                return false;
            }
        }

        bool IsValidBatch(String^ batch) {
            try {
                int year = System::Convert::ToInt32(batch);
                return (year >= 2000 && year <= 2100); // Reasonable year range
            }
            catch (Exception^) {
                return false;
            }
        }

        // Event handlers for form controls
        void txtFirstName_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
            // Allow only letters, space, and backspace
            if (!Char::IsLetter(e->KeyChar) && !Char::IsControl(e->KeyChar) && !Char::IsWhiteSpace(e->KeyChar)) {
                e->Handled = true;
            }
        }

        void txtLastName_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
            // Allow only letters, space, and backspace
            if (!Char::IsLetter(e->KeyChar) && !Char::IsControl(e->KeyChar) && !Char::IsWhiteSpace(e->KeyChar)) {
                e->Handled = true;
            }
        }

        void txtBatch_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
            // Allow only numbers and backspace
            if (!Char::IsDigit(e->KeyChar) && !Char::IsControl(e->KeyChar)) {
                e->Handled = true;
            }
        }

    protected:
        // Override the OnLoad method to perform additional initialization
        virtual void OnLoad(EventArgs^ e) override {
            Form::OnLoad(e);

            // Add event handlers for input validation
            txtFirstName->KeyPress += gcnew KeyPressEventHandler(this, &StudentProfileForm::txtFirstName_KeyPress);
            txtLastName->KeyPress += gcnew KeyPressEventHandler(this, &StudentProfileForm::txtLastName_KeyPress);
            txtBatch->KeyPress += gcnew KeyPressEventHandler(this, &StudentProfileForm::txtBatch_KeyPress);
        }
    };
}