#pragma once
using namespace System;
namespace UniversityManagementSystem {
   public ref class FacultyProfileForm : public System::Windows::Forms::Form {
    private:
        // Form components
        System::ComponentModel::Container^ components;
        System::Windows::Forms::TextBox^ txtFacultyID;
        System::Windows::Forms::TextBox^ txtFirstName;
        System::Windows::Forms::TextBox^ txtLastName;
        System::Windows::Forms::TextBox^ txtEmail;
        System::Windows::Forms::TextBox^ txtPhone;
        System::Windows::Forms::TextBox^ txtOffice;
        System::Windows::Forms::ComboBox^ cmbDepartment;
        System::Windows::Forms::DateTimePicker^ dtpDateOfAppointment;
        System::Windows::Forms::ComboBox^ cmbTitle;
        System::Windows::Forms::RichTextBox^ txtSpecialization;
        System::Windows::Forms::PictureBox^ picFacultyPhoto;
        System::Windows::Forms::Button^ btnUploadPhoto;
        System::Windows::Forms::Button^ btnSave;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Label^ lblFacultyID;
        System::Windows::Forms::Label^ lblFirstName;
        System::Windows::Forms::Label^ lblLastName;
        System::Windows::Forms::Label^ lblEmail;
        System::Windows::Forms::Label^ lblPhone;
        System::Windows::Forms::Label^ lblOffice;
        System::Windows::Forms::Label^ lblDepartment;
        System::Windows::Forms::Label^ lblDateOfAppointment;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::Label^ lblSpecialization;
        System::Windows::Forms::GroupBox^ grpPersonalInfo;
        System::Windows::Forms::GroupBox^ grpAcademicInfo;

    public:
        FacultyProfileForm(String^ facultyID)
        {
            InitializeComponent();
            LoadFacultyData(facultyID);
        }

    protected:
        ~FacultyProfileForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        void InitializeComponent(void)
        {
            // Form settings
            this->Text = L"Faculty Profile";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->Size = System::Drawing::Size(800, 700);

            // Initialize components
            this->components = gcnew System::ComponentModel::Container();
            this->grpPersonalInfo = gcnew System::Windows::Forms::GroupBox();
            this->grpAcademicInfo = gcnew System::Windows::Forms::GroupBox();

            // Initialize controls
            this->txtFacultyID = gcnew System::Windows::Forms::TextBox();
            this->txtFirstName = gcnew System::Windows::Forms::TextBox();
            this->txtLastName = gcnew System::Windows::Forms::TextBox();
            this->txtEmail = gcnew System::Windows::Forms::TextBox();
            this->txtPhone = gcnew System::Windows::Forms::TextBox();
            this->txtOffice = gcnew System::Windows::Forms::TextBox();
            this->cmbDepartment = gcnew System::Windows::Forms::ComboBox();
            this->dtpDateOfAppointment = gcnew System::Windows::Forms::DateTimePicker();
            this->cmbTitle = gcnew System::Windows::Forms::ComboBox();
            this->txtSpecialization = gcnew System::Windows::Forms::RichTextBox();
            this->picFacultyPhoto = gcnew System::Windows::Forms::PictureBox();
            this->btnUploadPhoto = gcnew System::Windows::Forms::Button();
            this->btnSave = gcnew System::Windows::Forms::Button();
            this->btnUpdate = gcnew System::Windows::Forms::Button();

            // Initialize labels
            this->lblFacultyID = gcnew System::Windows::Forms::Label();
            this->lblFirstName = gcnew System::Windows::Forms::Label();
            this->lblLastName = gcnew System::Windows::Forms::Label();
            this->lblEmail = gcnew System::Windows::Forms::Label();
            this->lblPhone = gcnew System::Windows::Forms::Label();
            this->lblOffice = gcnew System::Windows::Forms::Label();
            this->lblDepartment = gcnew System::Windows::Forms::Label();
            this->lblDateOfAppointment = gcnew System::Windows::Forms::Label();
            this->lblTitle = gcnew System::Windows::Forms::Label();
            this->lblSpecialization = gcnew System::Windows::Forms::Label();

            // Configure GroupBoxes
            this->grpPersonalInfo->Text = L"Personal Information";
            this->grpPersonalInfo->Location = System::Drawing::Point(20, 20);
            this->grpPersonalInfo->Size = System::Drawing::Size(450, 300);

            this->grpAcademicInfo->Text = L"Academic Information";
            this->grpAcademicInfo->Location = System::Drawing::Point(20, 330);
            this->grpAcademicInfo->Size = System::Drawing::Size(450, 250);

            // Configure controls - Personal Info
            int labelX = 20;
            int controlX = 140;
            int currentY = 30;
            int spacing = 30;

            // Faculty ID
            this->lblFacultyID->Location = System::Drawing::Point(labelX, currentY);
            this->lblFacultyID->Text = L"Faculty ID:";
            this->lblFacultyID->AutoSize = true;

            this->txtFacultyID->Location = System::Drawing::Point(controlX, currentY);
            this->txtFacultyID->Size = System::Drawing::Size(100, 20);
            this->txtFacultyID->ReadOnly = true;

            // First Name
            currentY += spacing;
            this->lblFirstName->Location = System::Drawing::Point(labelX, currentY);
            this->lblFirstName->Text = L"First Name:";
            this->lblFirstName->AutoSize = true;

            this->txtFirstName->Location = System::Drawing::Point(controlX, currentY);
            this->txtFirstName->Size = System::Drawing::Size(200, 20);

            // Last Name
            currentY += spacing;
            this->lblLastName->Location = System::Drawing::Point(labelX, currentY);
            this->lblLastName->Text = L"Last Name:";
            this->lblLastName->AutoSize = true;

            this->txtLastName->Location = System::Drawing::Point(controlX, currentY);
            this->txtLastName->Size = System::Drawing::Size(200, 20);

            // Email
            currentY += spacing;
            this->lblEmail->Location = System::Drawing::Point(labelX, currentY);
            this->lblEmail->Text = L"Email:";
            this->lblEmail->AutoSize = true;

            this->txtEmail->Location = System::Drawing::Point(controlX, currentY);
            this->txtEmail->Size = System::Drawing::Size(250, 20);

            // Phone
            currentY += spacing;
            this->lblPhone->Location = System::Drawing::Point(labelX, currentY);
            this->lblPhone->Text = L"Phone:";
            this->lblPhone->AutoSize = true;

            this->txtPhone->Location = System::Drawing::Point(controlX, currentY);
            this->txtPhone->Size = System::Drawing::Size(150, 20);

            // Office
            currentY += spacing;
            this->lblOffice->Location = System::Drawing::Point(labelX, currentY);
            this->lblOffice->Text = L"Office:";
            this->lblOffice->AutoSize = true;

            this->txtOffice->Location = System::Drawing::Point(controlX, currentY);
            this->txtOffice->Size = System::Drawing::Size(100, 20);

            // Configure controls - Academic Info
            currentY = 30;

            // Department
            this->lblDepartment->Location = System::Drawing::Point(labelX, currentY);
            this->lblDepartment->Text = L"Department:";
            this->lblDepartment->AutoSize = true;

            this->cmbDepartment->Location = System::Drawing::Point(controlX, currentY);
            this->cmbDepartment->Size = System::Drawing::Size(250, 21);
            this->cmbDepartment->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;

            // Title
            currentY += spacing;
            this->lblTitle->Location = System::Drawing::Point(labelX, currentY);
            this->lblTitle->Text = L"Title:";
            this->lblTitle->AutoSize = true;

            this->cmbTitle->Location = System::Drawing::Point(controlX, currentY);
            this->cmbTitle->Size = System::Drawing::Size(200, 21);
            this->cmbTitle->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbTitle->Items->AddRange(gcnew cli::array<System::Object^>(5) {
                L"Professor",
                    L"Associate Professor",
                    L"Assistant Professor",
                    L"Senior Lecturer",
                    L"Lecturer"
            });

            // Date of Appointment
            currentY += spacing;
            this->lblDateOfAppointment->Location = System::Drawing::Point(labelX, currentY);
            this->lblDateOfAppointment->Text = L"Date of Appointment:";
            this->lblDateOfAppointment->AutoSize = true;

            this->dtpDateOfAppointment->Location = System::Drawing::Point(controlX, currentY);
            this->dtpDateOfAppointment->Size = System::Drawing::Size(200, 20);
            this->dtpDateOfAppointment->Format = System::Windows::Forms::DateTimePickerFormat::Short;

            // Specialization
            currentY += spacing;
            this->lblSpecialization->Location = System::Drawing::Point(labelX, currentY);
            this->lblSpecialization->Text = L"Specialization:";
            this->lblSpecialization->AutoSize = true;

            this->txtSpecialization->Location = System::Drawing::Point(controlX, currentY);
            this->txtSpecialization->Size = System::Drawing::Size(250, 80);

            // Configure Photo Section
            this->picFacultyPhoto->Location = System::Drawing::Point(500, 30);
            this->picFacultyPhoto->Size = System::Drawing::Size(150, 150);
            this->picFacultyPhoto->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->picFacultyPhoto->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

            this->btnUploadPhoto->Location = System::Drawing::Point(500, 190);
            this->btnUploadPhoto->Size = System::Drawing::Size(150, 30);
            this->btnUploadPhoto->Text = L"Upload Photo";

            // Configure buttons
            this->btnSave->Location = System::Drawing::Point(500, 600);
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Text = L"Save";

            this->btnUpdate->Location = System::Drawing::Point(610, 600);
            this->btnUpdate->Size = System::Drawing::Size(100, 30);
            this->btnUpdate->Text = L"Update";
            this->btnUpdate->Enabled = false;

            // Add controls to Personal Info GroupBox
            this->grpPersonalInfo->Controls->Add(this->lblFacultyID);
            this->grpPersonalInfo->Controls->Add(this->lblFirstName);
            this->grpPersonalInfo->Controls->Add(this->lblLastName);
            this->grpPersonalInfo->Controls->Add(this->lblEmail);
            this->grpPersonalInfo->Controls->Add(this->lblPhone);
            this->grpPersonalInfo->Controls->Add(this->lblOffice);
            this->grpPersonalInfo->Controls->Add(this->txtFacultyID);
            this->grpPersonalInfo->Controls->Add(this->txtFirstName);
            this->grpPersonalInfo->Controls->Add(this->txtLastName);
            this->grpPersonalInfo->Controls->Add(this->txtEmail);
            this->grpPersonalInfo->Controls->Add(this->txtPhone);
            this->grpPersonalInfo->Controls->Add(this->txtOffice);

            // Add controls to Academic Info GroupBox
            this->grpAcademicInfo->Controls->Add(this->lblDepartment);
            this->grpAcademicInfo->Controls->Add(this->lblTitle);
            this->grpAcademicInfo->Controls->Add(this->lblDateOfAppointment);
            this->grpAcademicInfo->Controls->Add(this->lblSpecialization);
            this->grpAcademicInfo->Controls->Add(this->cmbDepartment);
            this->grpAcademicInfo->Controls->Add(this->cmbTitle);
            this->grpAcademicInfo->Controls->Add(this->dtpDateOfAppointment);
            this->grpAcademicInfo->Controls->Add(this->txtSpecialization);

            // Add controls to form
            this->Controls->Add(this->grpPersonalInfo);
            this->Controls->Add(this->grpAcademicInfo);
            this->Controls->Add(this->picFacultyPhoto);
            this->Controls->Add(this->btnUploadPhoto);
            this->Controls->Add(this->btnSave);
            this->Controls->Add(this->btnUpdate);

            // Wire up event handlers
            this->btnSave->Click += gcnew System::EventHandler(this, &FacultyProfileForm::btnSave_Click);
            this->btnUpdate->Click += gcnew System::EventHandler(this, &FacultyProfileForm::btnUpdate_Click);
            this->btnUploadPhoto->Click += gcnew System::EventHandler(this, &FacultyProfileForm::btnUploadPhoto_Click);
        }

        // Event handlers
        void btnSave_Click(System::Object^ sender, System::EventArgs^ e);
        void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e);
        void btnUploadPhoto_Click(System::Object^ sender, System::EventArgs^ e);
        void LoadFacultyData(String^ facultyID);
        void LoadDepartments();
        bool ValidateInput();
    };
}