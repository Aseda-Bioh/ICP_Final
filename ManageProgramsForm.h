#pragma once
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    public ref class ManageProgramsForm : public System::Windows::Forms::Form
    {
    public:
        ManageProgramsForm(void)
        {
            InitializeComponent();
            LoadPrograms();
            LoadDepartments();
        }

    protected:
        ~ManageProgramsForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::DataGridView^ dgvPrograms;
        System::Windows::Forms::TextBox^ txtProgramCode;
        System::Windows::Forms::TextBox^ txtProgramName;
        System::Windows::Forms::ComboBox^ cboDepartment;
        System::Windows::Forms::ComboBox^ cboDegreeLevel;
        System::Windows::Forms::NumericUpDown^ numCredits;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnUpdate;
        System::Windows::Forms::Button^ btnDelete;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Label^ lblProgramCode;
        System::Windows::Forms::Label^ lblProgramName;
        System::Windows::Forms::Label^ lblDepartment;
        System::Windows::Forms::Label^ lblDegreeLevel;
        System::Windows::Forms::Label^ lblCredits;

        System::ComponentModel::Container^ components;
        String^ connectionString = "Server=localhost;Database=university_system;Uid=aseda;Pwd=FatherAbraham2";

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Text = L"Manage Academic Programs";
            this->Size = System::Drawing::Size(800, 600);

            // Initialize components
            this->dgvPrograms = gcnew DataGridView();
            this->txtProgramCode = gcnew TextBox();
            this->txtProgramName = gcnew TextBox();
            this->cboDepartment = gcnew ComboBox();
            this->cboDegreeLevel = gcnew ComboBox();
            this->numCredits = gcnew NumericUpDown();
            this->btnAdd = gcnew Button();
            this->btnUpdate = gcnew Button();
            this->btnDelete = gcnew Button();
            this->btnRefresh = gcnew Button();
            this->lblProgramCode = gcnew Label();
            this->lblProgramName = gcnew Label();
            this->lblDepartment = gcnew Label();
            this->lblDegreeLevel = gcnew Label();
            this->lblCredits = gcnew Label();

            // DataGridView
            this->dgvPrograms->Location = System::Drawing::Point(20, 20);
            this->dgvPrograms->Size = System::Drawing::Size(760, 300);
            this->dgvPrograms->AllowUserToAddRows = false;
            this->dgvPrograms->AllowUserToDeleteRows = false;
            this->dgvPrograms->MultiSelect = false;
            this->dgvPrograms->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvPrograms->ReadOnly = true;
            this->dgvPrograms->SelectionChanged += gcnew EventHandler(this, &ManageProgramsForm::dgvPrograms_SelectionChanged);

            // Labels
            this->lblProgramCode->Text = L"Program Code:";
            this->lblProgramCode->Location = System::Drawing::Point(20, 340);
            this->lblProgramCode->AutoSize = true;

            this->lblProgramName->Text = L"Program Name:";
            this->lblProgramName->Location = System::Drawing::Point(20, 370);
            this->lblProgramName->AutoSize = true;

            this->lblDepartment->Text = L"Department:";
            this->lblDepartment->Location = System::Drawing::Point(20, 400);
            this->lblDepartment->AutoSize = true;

            this->lblDegreeLevel->Text = L"Degree Level:";
            this->lblDegreeLevel->Location = System::Drawing::Point(20, 430);
            this->lblDegreeLevel->AutoSize = true;

            this->lblCredits->Text = L"Required Credits:";
            this->lblCredits->Location = System::Drawing::Point(20, 460);
            this->lblCredits->AutoSize = true;

            // Input controls
            this->txtProgramCode->Location = System::Drawing::Point(150, 340);
            this->txtProgramCode->Size = System::Drawing::Size(100, 20);
            this->txtProgramCode->MaxLength = 10;

            this->txtProgramName->Location = System::Drawing::Point(150, 370);
            this->txtProgramName->Size = System::Drawing::Size(300, 20);
            this->txtProgramName->MaxLength = 100;

            this->cboDepartment->Location = System::Drawing::Point(150, 400);
            this->cboDepartment->Size = System::Drawing::Size(200, 20);
            this->cboDepartment->DropDownStyle = ComboBoxStyle::DropDownList;

            this->cboDegreeLevel->Location = System::Drawing::Point(150, 430);
            this->cboDegreeLevel->Size = System::Drawing::Size(200, 20);
            this->cboDegreeLevel->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cboDegreeLevel->Items->AddRange(gcnew array<String^> {
                "UNDERGRADUATE", "GRADUATE", "DOCTORAL"
            });

            this->numCredits->Location = System::Drawing::Point(150, 460);
            this->numCredits->Size = System::Drawing::Size(100, 20);
            this->numCredits->Minimum = 0;
            this->numCredits->Maximum = 200;
            this->numCredits->Value = 120;

            // Buttons
            this->btnAdd->Text = L"Add Program";
            this->btnAdd->Location = System::Drawing::Point(150, 500);
            this->btnAdd->Size = System::Drawing::Size(100, 30);
            this->btnAdd->Click += gcnew EventHandler(this, &ManageProgramsForm::btnAdd_Click);

            this->btnUpdate->Text = L"Update Program";
            this->btnUpdate->Location = System::Drawing::Point(260, 500);
            this->btnUpdate->Size = System::Drawing::Size(100, 30);
            this->btnUpdate->Click += gcnew EventHandler(this, &ManageProgramsForm::btnUpdate_Click);

            this->btnDelete->Text = L"Delete Program";
            this->btnDelete->Location = System::Drawing::Point(370, 500);
            this->btnDelete->Size = System::Drawing::Size(100, 30);
            this->btnDelete->Click += gcnew EventHandler(this, &ManageProgramsForm::btnDelete_Click);

            this->btnRefresh->Text = L"Refresh";
            this->btnRefresh->Location = System::Drawing::Point(480, 500);
            this->btnRefresh->Size = System::Drawing::Size(100, 30);
            this->btnRefresh->Click += gcnew EventHandler(this, &ManageProgramsForm::btnRefresh_Click);

            // Add controls to form
            this->Controls->Add(this->dgvPrograms);
            this->Controls->Add(this->lblProgramCode);
            this->Controls->Add(this->lblProgramName);
            this->Controls->Add(this->lblDepartment);
            this->Controls->Add(this->lblDegreeLevel);
            this->Controls->Add(this->lblCredits);
            this->Controls->Add(this->txtProgramCode);
            this->Controls->Add(this->txtProgramName);
            this->Controls->Add(this->cboDepartment);
            this->Controls->Add(this->cboDegreeLevel);
            this->Controls->Add(this->numCredits);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnUpdate);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->btnRefresh);
        }

        void LoadPrograms()
        {
            try
            {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(
                    "SELECT p.id, p.programCode, p.programName, p.departmentCode, "
                    "p.degreeLevel, p.creditRequirement, p.isActive, d.departmentName "
                    "FROM academic_program p "
                    "JOIN department d ON p.departmentCode = d.departmentCode "
                    "ORDER BY p.programCode", conn);

                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);
                dgvPrograms->DataSource = dt;

                // Configure columns
                dgvPrograms->Columns["id"]->Visible = false;
                dgvPrograms->Columns["programCode"]->HeaderText = "Program Code";
                dgvPrograms->Columns["programName"]->HeaderText = "Program Name";
                dgvPrograms->Columns["departmentCode"]->HeaderText = "Department Code";
                dgvPrograms->Columns["degreeLevel"]->HeaderText = "Degree Level";
                dgvPrograms->Columns["creditRequirement"]->HeaderText = "Credits Required";
                dgvPrograms->Columns["isActive"]->HeaderText = "Active";
                dgvPrograms->Columns["departmentName"]->HeaderText = "Department";
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error loading programs: " + ex->Message);
            }
        }

        void LoadDepartments()
        {
            try
            {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(
                    "SELECT departmentCode, departmentName FROM department WHERE isActive = 1",
                    conn);

                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);

                cboDepartment->DisplayMember = "departmentName";
                cboDepartment->ValueMember = "departmentCode";
                cboDepartment->DataSource = dt;
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error loading departments: " + ex->Message);
            }
        }

        void ClearInputs()
        {
            txtProgramCode->Clear();
            txtProgramName->Clear();
            cboDepartment->SelectedIndex = -1;
            cboDegreeLevel->SelectedIndex = -1;
            numCredits->Value = 120;
        }

        bool ValidateInputs()
        {
            if (String::IsNullOrEmpty(txtProgramCode->Text->Trim()))
            {
                MessageBox::Show("Please enter a program code.");
                return false;
            }
            if (String::IsNullOrEmpty(txtProgramName->Text->Trim()))
            {
                MessageBox::Show("Please enter a program name.");
                return false;
            }
            if (cboDepartment->SelectedValue == nullptr)
            {
                MessageBox::Show("Please select a department.");
                return false;
            }
            if (cboDegreeLevel->SelectedItem == nullptr)
            {
                MessageBox::Show("Please select a degree level.");
                return false;
            }
            return true;
        }

        void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (!ValidateInputs()) return;

            try
            {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "INSERT INTO academic_program (programCode, programName, departmentCode, "
                    "degreeLevel, creditRequirement) VALUES (@code, @name, @dept, @level, @credits)",
                    conn);

                cmd->Parameters->AddWithValue("@code", txtProgramCode->Text->Trim());
                cmd->Parameters->AddWithValue("@name", txtProgramName->Text->Trim());
                cmd->Parameters->AddWithValue("@dept", cboDepartment->SelectedValue->ToString());
                cmd->Parameters->AddWithValue("@level", cboDegreeLevel->SelectedItem->ToString());
                cmd->Parameters->AddWithValue("@credits", numCredits->Value);

                conn->Open();
                cmd->ExecuteNonQuery();
                MessageBox::Show("Program added successfully!");

                ClearInputs();
                LoadPrograms();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error adding program: " + ex->Message);
            }
        }

        void dgvPrograms_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (dgvPrograms->SelectedRows->Count > 0)
            {
                DataGridViewRow^ row = dgvPrograms->SelectedRows[0];
                txtProgramCode->Text = row->Cells["programCode"]->Value->ToString();
                txtProgramName->Text = row->Cells["programName"]->Value->ToString();
                cboDepartment->SelectedValue = row->Cells["departmentCode"]->Value->ToString();
                cboDegreeLevel->SelectedItem = row->Cells["degreeLevel"]->Value->ToString();
                numCredits->Value = Convert::ToDecimal(row->Cells["creditRequirement"]->Value);
            }
        }

        void btnUpdate_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dgvPrograms->SelectedRows->Count == 0)
            {
                MessageBox::Show("Please select a program to update.");
                return;
            }

            if (!ValidateInputs()) return;

            try
            {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "UPDATE academic_program SET programName = @name, departmentCode = @dept, "
                    "degreeLevel = @level, creditRequirement = @credits "
                    "WHERE programCode = @code", conn);

                cmd->Parameters->AddWithValue("@name", txtProgramName->Text->Trim());
                cmd->Parameters->AddWithValue("@dept", cboDepartment->SelectedValue->ToString());
                cmd->Parameters->AddWithValue("@level", cboDegreeLevel->SelectedItem->ToString());
                cmd->Parameters->AddWithValue("@credits", numCredits->Value);
                cmd->Parameters->AddWithValue("@code", txtProgramCode->Text->Trim());

                conn->Open();
                int rowsAffected = cmd->ExecuteNonQuery();
                if (rowsAffected > 0)
                {
                    MessageBox::Show("Program updated successfully!");
                    LoadPrograms();
                }
                else
                {
                    MessageBox::Show("Program not found.");
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error updating program: " + ex->Message);
            }
        }

        void btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dgvPrograms->SelectedRows->Count == 0)
            {
                MessageBox::Show("Please select a program to delete.");
                return;
            }

            if (MessageBox::Show("Are you sure you want to delete this program?",
                "Confirm Delete", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) ==
                System::Windows::Forms::DialogResult::No)
            {
                return;
            }

            try
            {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                // Instead of actually deleting, we'll set isActive to 0
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "UPDATE academic_program SET isActive = 0 WHERE programCode = @code",
                    conn);

                cmd->Parameters->AddWithValue("@code", txtProgramCode->Text->Trim());

                conn->Open();
                int rowsAffected = cmd->ExecuteNonQuery();
                if (rowsAffected > 0)
                {
                    MessageBox::Show("Program deleted successfully!");
                    ClearInputs();
                    LoadPrograms();
                }
                else
                {
                    MessageBox::Show("Program not found.");
                }
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error deleting program: " + ex->Message);
            }
        }

        void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e)
        {
            ClearInputs();
            LoadPrograms();
            LoadDepartments();
        }
    };
}