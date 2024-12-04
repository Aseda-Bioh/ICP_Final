#pragma once
namespace UniversityManagementSystem {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace MySql::Data::MySqlClient;
    using namespace System::IO;

    public ref class ReportGenerationForm : public System::Windows::Forms::Form
    {
    public:
        ReportGenerationForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~ReportGenerationForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        // Form controls
        System::Windows::Forms::GroupBox^ grpReportType;
        System::Windows::Forms::GroupBox^ grpFilters;
        System::Windows::Forms::ComboBox^ cboReportType;
        System::Windows::Forms::ComboBox^ cboDepartment;
        System::Windows::Forms::ComboBox^ cboProgram;
        System::Windows::Forms::ComboBox^ cboTerm;
        System::Windows::Forms::DateTimePicker^ dtpStartDate;
        System::Windows::Forms::DateTimePicker^ dtpEndDate;
        System::Windows::Forms::DataGridView^ dgvReport;
        System::Windows::Forms::Button^ btnGenerate;
        System::Windows::Forms::Button^ btnExport;
        System::Windows::Forms::Button^ btnPrint;
        System::Windows::Forms::Label^ lblReportType;
        System::Windows::Forms::Label^ lblDepartment;
        System::Windows::Forms::Label^ lblProgram;
        System::Windows::Forms::Label^ lblTerm;
        System::Windows::Forms::Label^ lblDateRange;

        System::ComponentModel::Container^ components;
        String^ connectionString = "Server=localhost;Database=university_system;Uid=aseda;Pwd=FatherAbraham2";

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Text = L"Report Generation";
            this->Size = System::Drawing::Size(1200, 800);

            // Initialize GroupBoxes
            this->grpReportType = gcnew GroupBox();
            this->grpReportType->Text = L"Report Configuration";
            this->grpReportType->Location = System::Drawing::Point(20, 20);
            this->grpReportType->Size = System::Drawing::Size(1140, 150);

            this->grpFilters = gcnew GroupBox();
            this->grpFilters->Text = L"Filters";
            this->grpFilters->Location = System::Drawing::Point(20, 180);
            this->grpFilters->Size = System::Drawing::Size(1140, 100);

            // Initialize Controls
            this->lblReportType = gcnew Label();
            this->lblReportType->Text = L"Report Type:";
            this->lblReportType->Location = System::Drawing::Point(20, 30);
            this->lblReportType->AutoSize = true;

            this->cboReportType = gcnew ComboBox();
            this->cboReportType->Location = System::Drawing::Point(120, 30);
            this->cboReportType->Size = System::Drawing::Size(300, 21);
            this->cboReportType->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cboReportType->Items->AddRange(gcnew array<String^> {
                "Enrollment Statistics by Program",
                    "Grade Distribution Report",
                    "Faculty Teaching Load Report",
                    "Course Enrollment Report",
                    "Student Performance Report"
            });
            this->cboReportType->SelectedIndexChanged += gcnew EventHandler(this, &ReportGenerationForm::cboReportType_SelectedIndexChanged);

            // Filter Controls
            this->lblDepartment = gcnew Label();
            this->lblDepartment->Text = L"Department:";
            this->lblDepartment->Location = System::Drawing::Point(20, 30);
            this->lblDepartment->AutoSize = true;

            this->cboDepartment = gcnew ComboBox();
            this->cboDepartment->Location = System::Drawing::Point(100, 30);
            this->cboDepartment->Size = System::Drawing::Size(200, 21);
            this->cboDepartment->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cboDepartment->SelectedIndexChanged += gcnew EventHandler(this, &ReportGenerationForm::cboDepartment_SelectedIndexChanged);

            this->lblProgram = gcnew Label();
            this->lblProgram->Text = L"Program:";
            this->lblProgram->Location = System::Drawing::Point(320, 30);
            this->lblProgram->AutoSize = true;

            this->cboProgram = gcnew ComboBox();
            this->cboProgram->Location = System::Drawing::Point(400, 30);
            this->cboProgram->Size = System::Drawing::Size(200, 21);
            this->cboProgram->DropDownStyle = ComboBoxStyle::DropDownList;

            this->lblTerm = gcnew Label();
            this->lblTerm->Text = L"Term:";
            this->lblTerm->Location = System::Drawing::Point(620, 30);
            this->lblTerm->AutoSize = true;

            this->cboTerm = gcnew ComboBox();
            this->cboTerm->Location = System::Drawing::Point(680, 30);
            this->cboTerm->Size = System::Drawing::Size(200, 21);
            this->cboTerm->DropDownStyle = ComboBoxStyle::DropDownList;

            // Date Range
            this->lblDateRange = gcnew Label();
            this->lblDateRange->Text = L"Date Range:";
            this->lblDateRange->Location = System::Drawing::Point(20, 60);
            this->lblDateRange->AutoSize = true;

            this->dtpStartDate = gcnew DateTimePicker();
            this->dtpStartDate->Location = System::Drawing::Point(100, 60);
            this->dtpStartDate->Size = System::Drawing::Size(200, 20);
            this->dtpStartDate->Format = DateTimePickerFormat::Short;

            this->dtpEndDate = gcnew DateTimePicker();
            this->dtpEndDate->Location = System::Drawing::Point(320, 60);
            this->dtpEndDate->Size = System::Drawing::Size(200, 20);
            this->dtpEndDate->Format = DateTimePickerFormat::Short;

            // Buttons
            this->btnGenerate = gcnew Button();
            this->btnGenerate->Text = L"Generate Report";
            this->btnGenerate->Location = System::Drawing::Point(900, 30);
            this->btnGenerate->Size = System::Drawing::Size(120, 30);
            this->btnGenerate->Click += gcnew EventHandler(this, &ReportGenerationForm::btnGenerate_Click);

            this->btnExport = gcnew Button();
            this->btnExport->Text = L"Export to Excel";
            this->btnExport->Location = System::Drawing::Point(900, 70);
            this->btnExport->Size = System::Drawing::Size(120, 30);
            this->btnExport->Click += gcnew EventHandler(this, &ReportGenerationForm::btnExport_Click);

            this->btnPrint = gcnew Button();
            this->btnPrint->Text = L"Print Report";
            this->btnPrint->Location = System::Drawing::Point(1030, 30);
            this->btnPrint->Size = System::Drawing::Size(90, 30);
            this->btnPrint->Click += gcnew EventHandler(this, &ReportGenerationForm::btnPrint_Click);

            // DataGridView for report display
            this->dgvReport = gcnew DataGridView();
            this->dgvReport->Location = System::Drawing::Point(20, 300);
            this->dgvReport->Size = System::Drawing::Size(1140, 440);
            this->dgvReport->AllowUserToAddRows = false;
            this->dgvReport->ReadOnly = true;
            this->dgvReport->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            // Add controls to GroupBoxes
            this->grpReportType->Controls->AddRange(gcnew array<Control^> {
                this->lblReportType, this->cboReportType
            });

            this->grpFilters->Controls->AddRange(gcnew array<Control^> {
                this->lblDepartment, this->cboDepartment,
                    this->lblProgram, this->cboProgram,
                    this->lblTerm, this->cboTerm,
                    this->lblDateRange, this->dtpStartDate, this->dtpEndDate
            });

            // Add controls to form
            this->Controls->Add(this->grpReportType);
            this->Controls->Add(this->grpFilters);
            this->Controls->Add(this->dgvReport);
            this->Controls->Add(this->btnGenerate);
            this->Controls->Add(this->btnExport);
            this->Controls->Add(this->btnPrint);

            // Load initial data
            LoadDepartments();
            LoadTerms();
        }

        void LoadDepartments()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand("SELECT departmentCode, departmentName FROM department WHERE isActive = 1", conn);
                conn->Open();

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);

                cboDepartment->DisplayMember = "departmentName";
                cboDepartment->ValueMember = "departmentCode";
                cboDepartment->DataSource = dt;

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading departments: " + ex->Message);
            }
        }

        void LoadPrograms(String^ departmentCode)
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "SELECT programCode, programName FROM academic_program "
                    "WHERE departmentCode = @dept AND isActive = 1", conn);
                cmd->Parameters->AddWithValue("@dept", departmentCode);

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

        void LoadTerms()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                MySqlCommand^ cmd = gcnew MySqlCommand(
                    "SELECT termCode, CONCAT(termCode, ' - ', termName) as termDisplay "
                    "FROM academic_term WHERE isActive = 1", conn);

                conn->Open();
                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);

                cboTerm->DisplayMember = "termDisplay";
                cboTerm->ValueMember = "termCode";
                cboTerm->DataSource = dt;

                conn->Close();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading terms: " + ex->Message);
            }
        }

        void GenerateEnrollmentReport()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                String^ query = "SELECT p.programCode, p.programName, p.degreeLevel, "
                    "COUNT(DISTINCT s.studentID) as totalStudents, "
                    "COUNT(DISTINCT CASE WHEN e.statusID = 1 THEN e.studentID END) as activeEnrollments "
                    "FROM academic_program p "
                    "LEFT JOIN student s ON p.programCode = s.programCode "
                    "LEFT JOIN enrollment e ON s.studentID = e.studentID "
                    "LEFT JOIN course_offering co ON e.courseOfferingID = co.id "
                    "WHERE p.departmentCode = @dept ";

                if (cboTerm->SelectedValue != nullptr) {
                    query += "AND co.termCode = @term ";
                }

                query += "GROUP BY p.programCode, p.programName, p.degreeLevel";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@dept", cboDepartment->SelectedValue->ToString());

                if (cboTerm->SelectedValue != nullptr) {
                    cmd->Parameters->AddWithValue("@term", cboTerm->SelectedValue->ToString());
                }

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);
                dgvReport->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error generating enrollment report: " + ex->Message);
            }
        }

        void cboDepartment_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            if (cboDepartment->SelectedValue != nullptr) {
                LoadPrograms(cboDepartment->SelectedValue->ToString());
            }
        }

        void cboReportType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            // Enable/disable relevant filters based on report type
            switch (cboReportType->SelectedIndex) {
            case 0: // Enrollment Statistics
                cboDepartment->Enabled = true;
                cboProgram->Enabled = true;
                cboTerm->Enabled = true;
                dtpStartDate->Enabled = false;
                dtpEndDate->Enabled = false;
                break;
                // Add other cases for different report types
            }
        }

        void btnGenerate_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (cboReportType->SelectedIndex == -1) {
                MessageBox::Show("Please select a report type.");
                return;
            }

            switch (cboReportType->SelectedIndex) {
            case 0:
                GenerateEnrollmentReport();
                break;
            case 1:
                GenerateGradeDistributionReport();
                break;
            case 2:
                GenerateFacultyLoadReport();
                break;
                // Add other cases for different report types
            }
        }

        void btnExport_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (dgvReport->Rows->Count == 0) {
                MessageBox::Show("No data to export.");
                return;
            }

            SaveFileDialog^ sfd = gcnew SaveFileDialog();
            sfd->Filter = "CSV Files (*.csv)|*.csv";
            sfd->FileName = "Report_" + DateTime::Now.ToString("yyyyMMdd_HHmmss") + ".csv";

            if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                try {
                    StreamWriter^ sw = gcnew StreamWriter(sfd->FileName);

                    // Write headers
                    for (int i = 0; i < dgvReport->Columns->Count; i++) {
                        sw->Write(dgvReport->Columns[i]->HeaderText);
                        if (i < dgvReport->Columns->Count - 1)
                            sw->Write(",");
                    }
                    sw->WriteLine();

                    // Write data
                    for (int i = 0; i < dgvReport->Rows->Count; i++) {
                        for (int j = 0; j < dgvReport->Columns->Count; j++) {
                            if (dgvReport->Rows[i]->Cells[j]->Value != nullptr) {
                                String^ value = dgvReport->Rows[i]->Cells[j]->Value->ToString();
                                // Escape commas and quotes
                                if (value->Contains(",") || value->Contains("\"")) {
                                    value = "\"" + value->Replace("\"", "\"\"") + "\"";
                                }
                                sw->Write(value);
                            }
                            if (j < dgvReport->Columns->Count - 1)
                                sw->Write(",");
                        }
                        sw->WriteLine();
                    }

                    sw->Close();
                    MessageBox::Show("Report exported successfully!");
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Error exporting report: " + ex->Message);
                }
            }
        }

        void btnPrint_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try {
                // Set up printing
                System::Drawing::Printing::PrintDocument^ printDoc =
                    gcnew System::Drawing::Printing::PrintDocument();
                printDoc->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(
                    this, &ReportGenerationForm::PrintPage);

                // Show print dialog
                System::Windows::Forms::PrintDialog^ printDialog =
                    gcnew System::Windows::Forms::PrintDialog();
                printDialog->Document = printDoc;

                if (printDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                    printDoc->Print();
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error printing report: " + ex->Message);
            }
        }

    
        void PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e)
        {
            // Print settings
            int startX = 50;
            int startY = 50;
            int cellHeight = 30;
            int cellPadding = 5;
            System::Drawing::Font^ headerFont = gcnew System::Drawing::Font("Arial", 10, FontStyle::Bold);
            System::Drawing::Font^ contentFont = gcnew System::Drawing::Font("Arial", 10);

            // Print title
            String^ reportTitle = "Report: " + cboReportType->Text;
            e->Graphics->DrawString(reportTitle, headerFont, Brushes::Black, startX, startY);
            startY += 40;

            // Print headers
            int currentX = startX;
            int columnWidth = (e->MarginBounds.Width - startX) / dgvReport->Columns->Count;

            for (int i = 0; i < dgvReport->Columns->Count; i++) {
                Rectangle rect = Rectangle(currentX, startY, columnWidth, cellHeight);
                e->Graphics->DrawRectangle(Pens::Black, rect);
                e->Graphics->DrawString(dgvReport->Columns[i]->HeaderText, headerFont,
                    Brushes::Black, rect.X + cellPadding, rect.Y + cellPadding);
                currentX += columnWidth;
            }
            startY += cellHeight;

            // Print data
            for (int row = 0; row < dgvReport->Rows->Count; row++) {
                currentX = startX;
                for (int col = 0; col < dgvReport->Columns->Count; col++) {
                    Rectangle rect = Rectangle(currentX, startY, columnWidth, cellHeight);
                    e->Graphics->DrawRectangle(Pens::Black, rect);
                    e->Graphics->DrawString(
                        dgvReport->Rows[row]->Cells[col]->Value->ToString(),
                        contentFont, Brushes::Black, rect.X + cellPadding, rect.Y + cellPadding);
                    currentX += columnWidth;
                }
                startY += cellHeight;
            }

            // Add footer with date and page number
            String^ footer = String::Format("Generated on: {0}", DateTime::Now.ToString());
            e->Graphics->DrawString(footer, contentFont, Brushes::Black,
                startX, e->MarginBounds.Bottom - 40);
        }

        void GenerateGradeDistributionReport()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                String^ query =
                    "SELECT c.courseCode, c.courseName, g.grade, "
                    "COUNT(*) as count, "
                    "ROUND(COUNT(*) * 100.0 / SUM(COUNT(*)) OVER(PARTITION BY c.courseCode), 2) as percentage "
                    "FROM course c "
                    "JOIN course_offering co ON c.courseCode = co.courseCode "
                    "JOIN enrollment e ON co.id = e.courseOfferingID "
                    "JOIN grade g ON e.id = g.enrollmentID "
                    "WHERE c.departmentCode = @dept ";

                if (cboTerm->SelectedValue != nullptr) {
                    query += "AND co.termCode = @term ";
                }
                if (cboProgram->SelectedValue != nullptr) {
                    query += "AND EXISTS (SELECT 1 FROM student s WHERE s.studentID = e.studentID "
                        "AND s.programCode = @program) ";
                }

                query += "GROUP BY c.courseCode, c.courseName, g.grade "
                    "ORDER BY c.courseCode, g.grade";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@dept", cboDepartment->SelectedValue->ToString());

                if (cboTerm->SelectedValue != nullptr) {
                    cmd->Parameters->AddWithValue("@term", cboTerm->SelectedValue->ToString());
                }
                if (cboProgram->SelectedValue != nullptr) {
                    cmd->Parameters->AddWithValue("@program", cboProgram->SelectedValue->ToString());
                }

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);
                dgvReport->DataSource = dt;

                // Format percentage column
                dgvReport->Columns["percentage"]->DefaultCellStyle->Format = "N2";
                dgvReport->Columns["percentage"]->DefaultCellStyle->Alignment = DataGridViewContentAlignment::MiddleRight;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error generating grade distribution report: " + ex->Message);
            }
        }

        void GenerateFacultyLoadReport()
        {
            try {
                MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
                String^ query =
                    "SELECT u.firstName, u.lastName, f.title, "
                    "COUNT(DISTINCT co.id) as courseCount, "
                    "SUM(co.enrolledCount) as totalStudents "
                    "FROM faculty f "
                    "JOIN user u ON f.userID = u.userID "
                    "JOIN course_offering co ON f.userID = co.facultyID "
                    "WHERE f.departmentCode = @dept ";

                if (cboTerm->SelectedValue != nullptr) {
                    query += "AND co.termCode = @term ";
                }

                query += "GROUP BY u.firstName, u.lastName, f.title";

                MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@dept", cboDepartment->SelectedValue->ToString());

                if (cboTerm->SelectedValue != nullptr) {
                    cmd->Parameters->AddWithValue("@term", cboTerm->SelectedValue->ToString());
                }

                MySqlDataAdapter^ da = gcnew MySqlDataAdapter(cmd);
                DataTable^ dt = gcnew DataTable();
                da->Fill(dt);
                dgvReport->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error generating faculty load report: " + ex->Message);
            }
        }
    };
}