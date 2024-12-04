#pragma once
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;

    /// <summary>
    /// StudentScheduleForm displays the current student's course schedule
    /// </summary>
    public ref class StudentScheduleForm : public System::Windows::Forms::Form
    {
    public:
        StudentScheduleForm(String^ studentID)
        {
            InitializeComponent();
            this->studentID = studentID;
            ConfigureDatabase();
        }
    
    public:
        virtual void OnLoad(EventArgs^ e) override {
            Form::OnLoad(e);
            try {
                UpdateStatus("Initializing...");
                LoadTerms();  // This will trigger LoadSchedule via the SelectedIndexChanged event
                UpdateStatus("Ready");
            }
            catch (Exception^ ex) {
                UpdateStatus("Error during initialization");
                MessageBox::Show("Error initializing form: " + ex->Message,
                    "Initialization Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

    protected:
        ~StudentScheduleForm()
        {
            if (components) {
                delete components;
            }
            if (sqlConnection) {
                sqlConnection->Close();
                delete sqlConnection;
            }
        }

    private:
        // Form components
        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridView^ dgvSchedule;
        System::Windows::Forms::ComboBox^ cmbTerm;
        System::Windows::Forms::Label^ lblTerm;
        System::Windows::Forms::Button^ btnRefresh;
        System::Windows::Forms::Panel^ pnlControls;
        System::Windows::Forms::Panel^ pnlGrid;
        System::Windows::Forms::StatusStrip^ statusStrip;
        System::Windows::Forms::ToolStripStatusLabel^ statusLabel;

        // Database components
        String^ studentID;
        MySqlConnection^ sqlConnection;

        /// <summary>
        /// Required method for Designer support
        /// </summary>
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();

            // Form settings
            this->Text = L"Student Schedule";
            this->Size = System::Drawing::Size(1024, 768);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MinimumSize = System::Drawing::Size(800, 600);
            this->WindowState = FormWindowState::Maximized;

            // Create control panel
            this->pnlControls = gcnew Panel();
            this->pnlControls->Dock = DockStyle::Top;
            this->pnlControls->Height = 60;
            this->pnlControls->Padding = System::Windows::Forms::Padding(10); 

            // Create grid panel (moved earlier)
            this->pnlGrid = gcnew Panel();
            this->pnlGrid->Dock = DockStyle::Fill;
            this->pnlGrid->Padding = System::Windows::Forms::Padding(10); 

            // Term Label
            this->lblTerm = gcnew Label();
            this->lblTerm->Text = L"Select Term:";
            this->lblTerm->Location = System::Drawing::Point(20, 20);
            this->lblTerm->AutoSize = true;
            this->pnlControls->Controls->Add(this->lblTerm);

            // Term Selector
            this->cmbTerm = gcnew ComboBox();
            this->cmbTerm->Location = System::Drawing::Point(120, 17);
            this->cmbTerm->Size = System::Drawing::Size(250, 25);
            this->cmbTerm->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbTerm->SelectedIndexChanged += gcnew EventHandler(this, &StudentScheduleForm::cmbTerm_SelectedIndexChanged);
            this->pnlControls->Controls->Add(this->cmbTerm);

            // Refresh Button
            this->btnRefresh = gcnew Button();
            this->btnRefresh->Text = L"Refresh";
            this->btnRefresh->Location = System::Drawing::Point(390, 16);
            this->btnRefresh->Size = System::Drawing::Size(100, 28);
            this->btnRefresh->Click += gcnew EventHandler(this, &StudentScheduleForm::btnRefresh_Click);
            this->pnlControls->Controls->Add(this->btnRefresh);

            // Schedule DataGridView
            this->dgvSchedule = gcnew DataGridView();
            this->dgvSchedule->Dock = DockStyle::Fill;
            this->dgvSchedule->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dgvSchedule->AllowUserToAddRows = false;
            this->dgvSchedule->AllowUserToDeleteRows = false;
            this->dgvSchedule->ReadOnly = true;
            this->dgvSchedule->MultiSelect = false;
            this->dgvSchedule->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dgvSchedule->RowHeadersVisible = false;
            this->dgvSchedule->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::AliceBlue;
            this->pnlGrid->Controls->Add(this->dgvSchedule);

            // Status Strip
            this->statusStrip = gcnew StatusStrip();
            this->statusLabel = gcnew ToolStripStatusLabel();
            this->statusStrip->Items->Add(this->statusLabel);

            // Add panels to form
            this->Controls->Add(this->pnlGrid);
            this->Controls->Add(this->pnlControls);
            this->Controls->Add(this->statusStrip);

            // Handle form events
            this->Load += gcnew EventHandler(this, &StudentScheduleForm::StudentScheduleForm_Load);
            this->Resize += gcnew EventHandler(this, &StudentScheduleForm::StudentScheduleForm_Resize);
        }

        void ConfigureDatabase(void)
        {
            try {
                String^ connectString = "server=localhost;port=3306;database=university_system;uid=aseda;password=FatherAbraham2";
                sqlConnection = gcnew MySqlConnection(connectString);
                UpdateStatus("Database connection configured successfully");
            }
            catch (Exception^ ex) {
                UpdateStatus("Database configuration error");
                MessageBox::Show("Database configuration error: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void LoadTerms(void)
        {
            try {
                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                String^ query = "SELECT DISTINCT at.termCode, at.termName "
                    "FROM academic_term at "
                    "INNER JOIN course_offering co ON at.termCode = co.termCode "
                    "INNER JOIN enrollment e ON co.id = e.courseOfferingID "
                    "WHERE e.studentID = @studentID AND e.statusID = 1 "
                    "ORDER BY at.termCode DESC";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                cmd->Parameters->AddWithValue("@studentID", this->studentID);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ table = gcnew DataTable();
                adapter->Fill(table);

                if (table->Rows->Count > 0) {
                    cmbTerm->DisplayMember = "termName";
                    cmbTerm->ValueMember = "termCode";
                    cmbTerm->DataSource = table;
                    UpdateStatus("Terms loaded successfully");
                }
                else {
                    UpdateStatus("No terms found");
                    MessageBox::Show("No enrolled terms found.", "Information",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
            }
            catch (Exception^ ex) {
                UpdateStatus("Error loading terms");
                MessageBox::Show("Error loading terms: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }
        }

        void LoadSchedule(void)
        {
            try {
                if (cmbTerm == nullptr || cmbTerm->SelectedValue == nullptr) {
                    dgvSchedule->DataSource = nullptr;
                    return;
                }

                String^ selectedTerm = cmbTerm->SelectedValue->ToString();
                if (String::IsNullOrEmpty(selectedTerm)) {
                    dgvSchedule->DataSource = nullptr;
                    return;
                }

                if (sqlConnection->State == ConnectionState::Closed)
                    sqlConnection->Open();

                String^ query = "SELECT c.courseCode as 'Course Code', "
                    "c.courseName as 'Course Name', "
                    "c.credits as 'Credits', "
                    "co.section as 'Section', "
                    "CONCAT(u.firstName, ' ', u.lastName) as 'Instructor', "
                    "cs.day_of_week as 'Day', "
                    "TIME_FORMAT(cs.start_time, '%H:%i') as 'Start Time', "
                    "TIME_FORMAT(cs.end_time, '%H:%i') as 'End Time', "
                    "cs.room_number as 'Room' "
                    "FROM enrollment e "
                    "INNER JOIN course_offering co ON e.courseOfferingID = co.id "
                    "INNER JOIN course c ON co.courseCode = c.courseCode "
                    "INNER JOIN faculty f ON co.facultyID = f.userID "
                    "INNER JOIN user u ON f.userID = u.userID "
                    "LEFT JOIN course_schedule cs ON co.id = cs.course_offering_id "
                    "WHERE e.studentID = @studentID "
                    "AND co.termCode = @termCode "
                    "AND e.statusID = 1 "
                    "ORDER BY cs.day_of_week, cs.start_time";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, sqlConnection);
                cmd->Parameters->AddWithValue("@studentID", this->studentID);
                cmd->Parameters->AddWithValue("@termCode", selectedTerm);

                MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter(cmd);
                DataTable^ table = gcnew DataTable();
                adapter->Fill(table);

                if (table->Rows->Count > 0) {
                    dgvSchedule->DataSource = table;
                    FormatGrid();
                    UpdateStatus(String::Format("Loaded {0} courses", table->Rows->Count));
                }
                else {
                    UpdateStatus("No courses found for selected term");
                    MessageBox::Show("No courses found for the selected term.", "Information",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
            }
            catch (Exception^ ex) {
                UpdateStatus("Error loading schedule");
                MessageBox::Show("Error loading schedule: " + ex->Message,
                    "Database Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally {
                if (sqlConnection->State == ConnectionState::Open)
                    sqlConnection->Close();
            }
        }

        void FormatGrid(void)
        {
            if (dgvSchedule->Columns->Count > 0) {
                try {
                    // Set column widths
                    if (dgvSchedule->Columns->Contains("Course Code"))
                        dgvSchedule->Columns["Course Code"]->Width = 100;

                    if (dgvSchedule->Columns->Contains("Course Name"))
                        dgvSchedule->Columns["Course Name"]->Width = 200;

                    if (dgvSchedule->Columns->Contains("Credits"))
                        dgvSchedule->Columns["Credits"]->Width = 70;

                    if (dgvSchedule->Columns->Contains("Section"))
                        dgvSchedule->Columns["Section"]->Width = 70;

                    if (dgvSchedule->Columns->Contains("Instructor"))
                        dgvSchedule->Columns["Instructor"]->Width = 150;

                    if (dgvSchedule->Columns->Contains("Day"))
                        dgvSchedule->Columns["Day"]->Width = 100;

                    if (dgvSchedule->Columns->Contains("Start Time"))
                        dgvSchedule->Columns["Start Time"]->Width = 100;

                    if (dgvSchedule->Columns->Contains("End Time"))
                        dgvSchedule->Columns["End Time"]->Width = 100;

                    if (dgvSchedule->Columns->Contains("Room"))
                        dgvSchedule->Columns["Room"]->Width = 100;

                    // Center align certain columns
                    if (dgvSchedule->Columns->Contains("Credits"))
                        dgvSchedule->Columns["Credits"]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;

                    if (dgvSchedule->Columns->Contains("Section"))
                        dgvSchedule->Columns["Section"]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;

                    if (dgvSchedule->Columns->Contains("Day"))
                        dgvSchedule->Columns["Day"]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;

                    if (dgvSchedule->Columns->Contains("Start Time"))
                        dgvSchedule->Columns["Start Time"]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;

                    if (dgvSchedule->Columns->Contains("End Time"))
                        dgvSchedule->Columns["End Time"]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;

                    if (dgvSchedule->Columns->Contains("Room"))
                        dgvSchedule->Columns["Room"]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleCenter;
                }
                catch (Exception^ ex) {
                    UpdateStatus("Error formatting grid: " + ex->Message);
                }
            }
        }

        void UpdateStatus(String^ message)
        {
            this->statusLabel->Text = message;
            this->statusStrip->Refresh();
        }

        // Event Handlers
        System::Void StudentScheduleForm_Load(System::Object^ sender, System::EventArgs^ e) {
            UpdateStatus("Loading schedule...");
            LoadTerms();
        }

        System::Void StudentScheduleForm_Resize(System::Object^ sender, System::EventArgs^ e) {
            FormatGrid();
        }

        System::Void cmbTerm_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
            LoadSchedule();
        }

        System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
            UpdateStatus("Refreshing schedule...");
            LoadSchedule();
        }
    };
}