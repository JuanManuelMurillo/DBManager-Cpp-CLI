#pragma once
#include <iostream>
#include <tchar.h>
#include <vcclr.h> 
#include <vector>
namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;
	using namespace System::Collections::Generic;



	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public: 
		System::String^ usuario = "usuario";
		bool dataChanged;
		bool ableToDelete;
		DataTable^ dataTableCopy = gcnew DataTable();
		List<Tuple<int, int>^>^ modifiedCells = gcnew List<Tuple<int, int>^>();
		
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::DataGridView^ DBView;
	private: System::Windows::Forms::Button^ bAceptar;
	private: System::Windows::Forms::CheckedListBox^ cbConnection;
	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::Button^ bClearDBView;




	public:
		System::String^ contrasenia = "contraseña";
	private: System::Windows::Forms::TextBox^ textBox1;
	public:

	private: System::Windows::Forms::ComboBox^ comboBox1;

	private: System::Windows::Forms::Button^ button2;

	private: System::Windows::Forms::Button^ ConnectDBButton;
	private: System::Windows::Forms::ComboBox^ comboBox2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ cambiosLabel;
	private: System::Windows::Forms::CheckBox^ editCheckBox;
	private: System::Windows::Forms::Button^ helpButton;
	private: System::Windows::Forms::GroupBox^ groupBox6;









		   bool logIn;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	//private: String^ connectionString = connectionTB->Text->ToString();
	//private: String^ connectionString = "datasource=localhost; username=root; password=password; database=ESR_DB";
	//private: MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
	private: System::Windows::Forms::Label^ lbUsuario;
	private: System::Windows::Forms::Label^ lbContrasenia;
	private: System::Windows::Forms::TextBox^ tbUsuario;
	private: System::Windows::Forms::TextBox^ tbContraseña;
	private: DataColumnCollection^ columnas;
		void LoadDataFromDB(String^ columns, String^ table) {
			String^ connectionString = comboBox2->Text->ToString();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
			
			try {
				conn->Open();
				DataTable^ tableSchema = conn->GetSchema("Tables");
				DataTable^ dataTable = gcnew DataTable();
				
				if (systemString2std(columns) == "Todo") {
					MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter("SELECT * FROM "+ table, conn);
					adapter->Fill(dataTable);
					adapter->Fill(dataTableCopy);
				}
				else {
					MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter("SELECT "+ columns +" FROM "+table, conn);
					adapter->Fill(dataTable);
					adapter->Fill(dataTableCopy);
				}
				cbConnection->SetItemChecked(0, true);
				DBView->Columns->Clear();
				DBView->DataSource = dataTable;
				columnas = dataTable->Columns;
				comboBox1->Items->Clear();
				if (lbColumns->SelectedIndex != 0) {
					comboBox1->Items->Add(columnas[0]->ColumnName);
				}
				else {
					comboBox1->Items->Clear();
					for (int i = 0; i < columnas->Count; i++) {
						comboBox1->Items->Add(columnas[i]->ColumnName);
					}
				}
				if (!System::String::IsNullOrEmpty(textBox1->Text) || comboBox1->SelectedIndex >= 0) {
					if (columnas != nullptr && columnas->Count > 0)
					{
						String^ columnName = dataTable->Columns[0]->ColumnName;
						dataTable->DefaultView->RowFilter = comboBox1->Text->ToString() + " = " + "'" + textBox1->Text->ToString() + "'";
					}
					else
					{
						
					}
				}
				
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				cbConnection->SetItemChecked(0, false);

			}
			finally {
				conn->Close();
				
			}
		}

	private:
		void connectDataBase() {
			String^ connectionString = comboBox2->Text->ToString();
			MySqlConnection^ conn = gcnew MySqlConnection(connectionString);

			try {
				conn->Open();
				cbConnection->SetItemChecked(0, true);
				DataTable^ tableSchema = conn->GetSchema("Tables");
				DataTable^ dataTable = gcnew DataTable();
				cbTables->Items->Clear();
				

				for each (DataRow ^ row in tableSchema->Rows) {
					String^ tableName = safe_cast<String^>(row["TABLE_NAME"]);
					cbTables->Items->Add(tableName);
				}

			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				cbConnection->SetItemChecked(0, false);

			}
			finally {
				conn->Close();

			}
		}
	private: 
		void fillColumns() {
			if (! System::String::IsNullOrEmpty(cbTables->Text->ToString())) {
				String^ table = cbTables->SelectedItem->ToString();
				//String^ table = cbTables->Text->ToString();
				String^ connectionString = comboBox2->Text->ToString();
				MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
				conn->Open();
				MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter("SELECT * FROM " + table, conn);
				dataTable->Columns->Clear();
				adapter->Fill(dataTable);
				cbConnection->SetItemChecked(0, true);
				columnas = dataTable->Columns;
				lbColumns->Items->Clear();
				lbColumns->Items->Add("Todo");
				for (int i = 0; i < columnas->Count; i++) {
					lbColumns->Items->Add(columnas[i]->ColumnName);
				}
				conn->Close();
			}
		}
	protected:

	protected:





	private: System::Windows::Forms::Button^ botonIngreso;


	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::Label^ lbErrorLogIn;

	private: System::Windows::Forms::GroupBox^ groupBox2;

	private: System::Windows::Forms::ListBox^ lbColumns;
	private: System::Windows::Forms::ComboBox^ cbTables;

	private: System::Windows::Forms::Button^ button1;





	private: System::ComponentModel::IContainer^ components;

	protected:

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->lbUsuario = (gcnew System::Windows::Forms::Label());
			this->lbContrasenia = (gcnew System::Windows::Forms::Label());
			this->botonIngreso = (gcnew System::Windows::Forms::Button());
			this->tbUsuario = (gcnew System::Windows::Forms::TextBox());
			this->tbContraseña = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lbErrorLogIn = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->cbTables = (gcnew System::Windows::Forms::ComboBox());
			this->lbColumns = (gcnew System::Windows::Forms::ListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->helpButton = (gcnew System::Windows::Forms::Button());
			this->editCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->cambiosLabel = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->bClearDBView = (gcnew System::Windows::Forms::Button());
			this->bAceptar = (gcnew System::Windows::Forms::Button());
			this->DBView = (gcnew System::Windows::Forms::DataGridView());
			this->cbConnection = (gcnew System::Windows::Forms::CheckedListBox());
			this->ConnectDBButton = (gcnew System::Windows::Forms::Button());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DBView))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->SuspendLayout();
			// 
			// lbUsuario
			// 
			this->lbUsuario->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lbUsuario->AutoSize = true;
			this->lbUsuario->Location = System::Drawing::Point(16, 27);
			this->lbUsuario->Name = L"lbUsuario";
			this->lbUsuario->Size = System::Drawing::Size(54, 16);
			this->lbUsuario->TabIndex = 0;
			this->lbUsuario->Text = L"Usuario";
			// 
			// lbContrasenia
			// 
			this->lbContrasenia->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lbContrasenia->AutoSize = true;
			this->lbContrasenia->Location = System::Drawing::Point(16, 64);
			this->lbContrasenia->Name = L"lbContrasenia";
			this->lbContrasenia->Size = System::Drawing::Size(76, 16);
			this->lbContrasenia->TabIndex = 1;
			this->lbContrasenia->Text = L"Contraseña";
			// 
			// botonIngreso
			// 
			this->botonIngreso->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->botonIngreso->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(162)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->botonIngreso->ForeColor = System::Drawing::Color::Black;
			this->botonIngreso->Location = System::Drawing::Point(113, 121);
			this->botonIngreso->Name = L"botonIngreso";
			this->botonIngreso->Size = System::Drawing::Size(219, 51);
			this->botonIngreso->TabIndex = 2;
			this->botonIngreso->Text = L"Ingresar";
			this->botonIngreso->UseVisualStyleBackColor = false;
			this->botonIngreso->Click += gcnew System::EventHandler(this, &Form1::botonIngreso_Click);
			// 
			// tbUsuario
			// 
			this->tbUsuario->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tbUsuario->Location = System::Drawing::Point(113, 24);
			this->tbUsuario->Name = L"tbUsuario";
			this->tbUsuario->Size = System::Drawing::Size(219, 22);
			this->tbUsuario->TabIndex = 3;
			// 
			// tbContraseña
			// 
			this->tbContraseña->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tbContraseña->Location = System::Drawing::Point(113, 61);
			this->tbContraseña->Name = L"tbContraseña";
			this->tbContraseña->PasswordChar = '*';
			this->tbContraseña->Size = System::Drawing::Size(219, 22);
			this->tbContraseña->TabIndex = 4;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->lbErrorLogIn);
			this->groupBox1->Controls->Add(this->tbUsuario);
			this->groupBox1->Controls->Add(this->lbUsuario);
			this->groupBox1->Controls->Add(this->tbContraseña);
			this->groupBox1->Controls->Add(this->lbContrasenia);
			this->groupBox1->Controls->Add(this->botonIngreso);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(349, 178);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Ingreso";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// lbErrorLogIn
			// 
			this->lbErrorLogIn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->lbErrorLogIn->AutoSize = true;
			this->lbErrorLogIn->Location = System::Drawing::Point(92, 95);
			this->lbErrorLogIn->Name = L"lbErrorLogIn";
			this->lbErrorLogIn->Size = System::Drawing::Size(0, 16);
			this->lbErrorLogIn->TabIndex = 6;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->cbTables);
			this->groupBox2->Controls->Add(this->lbColumns);
			this->groupBox2->Location = System::Drawing::Point(797, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(622, 172);
			this->groupBox2->TabIndex = 9;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Consulta";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(289, 21);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 16);
			this->label2->TabIndex = 13;
			this->label2->Text = L"Columnas";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(50, 16);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Tablas";
			// 
			// cbTables
			// 
			this->cbTables->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
				static_cast<System::Int32>(static_cast<System::Byte>(219)));
			this->cbTables->FormattingEnabled = true;
			this->cbTables->Location = System::Drawing::Point(6, 37);
			this->cbTables->Name = L"cbTables";
			this->cbTables->Size = System::Drawing::Size(248, 24);
			this->cbTables->TabIndex = 11;
			this->cbTables->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbTables_SelectedIndexChanged);
			// 
			// lbColumns
			// 
			this->lbColumns->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(209)), static_cast<System::Int32>(static_cast<System::Byte>(209)),
				static_cast<System::Int32>(static_cast<System::Byte>(209)));
			this->lbColumns->FormattingEnabled = true;
			this->lbColumns->ItemHeight = 16;
			this->lbColumns->Location = System::Drawing::Point(292, 43);
			this->lbColumns->Name = L"lbColumns";
			this->lbColumns->Size = System::Drawing::Size(324, 116);
			this->lbColumns->TabIndex = 10;
			this->lbColumns->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::lbColumns_SelectedIndexChanged);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(162)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Location = System::Drawing::Point(128, 17);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(209, 127);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Guardar Cambios";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->helpButton);
			this->groupBox4->Controls->Add(this->groupBox5);
			this->groupBox4->Controls->Add(this->bClearDBView);
			this->groupBox4->Controls->Add(this->bAceptar);
			this->groupBox4->Controls->Add(this->DBView);
			this->groupBox4->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->groupBox4->Location = System::Drawing::Point(12, 196);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(1756, 606);
			this->groupBox4->TabIndex = 11;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Datos";
			this->groupBox4->Enter += gcnew System::EventHandler(this, &Form1::groupBox4_Enter);
			// 
			// helpButton
			// 
			this->helpButton->Location = System::Drawing::Point(1711, 569);
			this->helpButton->Name = L"helpButton";
			this->helpButton->Size = System::Drawing::Size(30, 31);
			this->helpButton->TabIndex = 15;
			this->helpButton->Text = L"\?";
			this->helpButton->UseVisualStyleBackColor = true;
			this->helpButton->Click += gcnew System::EventHandler(this, &Form1::button3_Click_1);
			// 
			// editCheckBox
			// 
			this->editCheckBox->AutoSize = true;
			this->editCheckBox->Location = System::Drawing::Point(3, 17);
			this->editCheckBox->Name = L"editCheckBox";
			this->editCheckBox->Size = System::Drawing::Size(74, 20);
			this->editCheckBox->TabIndex = 14;
			this->editCheckBox->Text = L"Edición";
			this->editCheckBox->UseVisualStyleBackColor = true;
			this->editCheckBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// cambiosLabel
			// 
			this->cambiosLabel->AutoSize = true;
			this->cambiosLabel->Location = System::Drawing::Point(0, 156);
			this->cambiosLabel->Name = L"cambiosLabel";
			this->cambiosLabel->Size = System::Drawing::Size(92, 16);
			this->cambiosLabel->TabIndex = 13;
			this->cambiosLabel->Text = L"SIN CAMBIOS";
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->button2);
			this->groupBox5->Controls->Add(this->comboBox1);
			this->groupBox5->Controls->Add(this->textBox1);
			this->groupBox5->Location = System::Drawing::Point(6, 21);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(1518, 52);
			this->groupBox5->TabIndex = 12;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Filtro";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(162)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->button2->Location = System::Drawing::Point(1368, 20);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(144, 25);
			this->button2->TabIndex = 13;
			this->button2->Text = L"Eliminar Filtros";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
				static_cast<System::Int32>(static_cast<System::Byte>(219)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(13, 18);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(300, 24);
			this->comboBox1->TabIndex = 6;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::comboBox1_SelectedIndexChanged_1);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(366, 20);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(913, 22);
			this->textBox1->TabIndex = 5;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// bClearDBView
			// 
			this->bClearDBView->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(162)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->bClearDBView->Location = System::Drawing::Point(1532, 338);
			this->bClearDBView->Name = L"bClearDBView";
			this->bClearDBView->Size = System::Drawing::Size(211, 101);
			this->bClearDBView->TabIndex = 3;
			this->bClearDBView->Text = L"Borrar";
			this->bClearDBView->UseVisualStyleBackColor = false;
			this->bClearDBView->Click += gcnew System::EventHandler(this, &Form1::bClearDBView_Click);
			// 
			// bAceptar
			// 
			this->bAceptar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(162)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->bAceptar->Location = System::Drawing::Point(1530, 99);
			this->bAceptar->Name = L"bAceptar";
			this->bAceptar->Size = System::Drawing::Size(211, 101);
			this->bAceptar->TabIndex = 1;
			this->bAceptar->Text = L"Aceptar";
			this->bAceptar->UseVisualStyleBackColor = false;
			this->bAceptar->Click += gcnew System::EventHandler(this, &Form1::bAceptar_Click);
			// 
			// DBView
			// 
			this->DBView->AllowUserToDeleteRows = false;
			this->DBView->AllowUserToOrderColumns = true;
			this->DBView->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(76)), static_cast<System::Int32>(static_cast<System::Byte>(76)),
				static_cast<System::Int32>(static_cast<System::Byte>(76)));
			this->DBView->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->DBView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			dataGridViewCellStyle5->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle5->BackColor = System::Drawing::Color::White;
			dataGridViewCellStyle5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle5->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle5->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle5->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle5->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->DBView->DefaultCellStyle = dataGridViewCellStyle5;
			this->DBView->Location = System::Drawing::Point(8, 99);
			this->DBView->Name = L"DBView";
			this->DBView->ReadOnly = true;
			this->DBView->RowHeadersWidth = 51;
			this->DBView->RowTemplate->Height = 24;
			this->DBView->Size = System::Drawing::Size(1518, 507);
			this->DBView->TabIndex = 0;
			this->DBView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellContentClick);
			this->DBView->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::DBView_CellValueChanged);
			// 
			// cbConnection
			// 
			this->cbConnection->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(209)), static_cast<System::Int32>(static_cast<System::Byte>(209)),
				static_cast<System::Int32>(static_cast<System::Byte>(209)));
			this->cbConnection->FormattingEnabled = true;
			this->cbConnection->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Conexión a BD", L"Inicio de Sesión" });
			this->cbConnection->Location = System::Drawing::Point(255, 111);
			this->cbConnection->Name = L"cbConnection";
			this->cbConnection->Size = System::Drawing::Size(146, 55);
			this->cbConnection->TabIndex = 2;
			this->cbConnection->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cbConnection_SelectedIndexChanged);
			// 
			// ConnectDBButton
			// 
			this->ConnectDBButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(162)),
				static_cast<System::Int32>(static_cast<System::Byte>(150)));
			this->ConnectDBButton->Location = System::Drawing::Point(6, 73);
			this->ConnectDBButton->Name = L"ConnectDBButton";
			this->ConnectDBButton->Size = System::Drawing::Size(80, 25);
			this->ConnectDBButton->TabIndex = 13;
			this->ConnectDBButton->Text = L"Conectar";
			this->ConnectDBButton->UseVisualStyleBackColor = false;
			this->ConnectDBButton->Click += gcnew System::EventHandler(this, &Form1::ConnectDBButton_Click);
			// 
			// comboBox2
			// 
			this->comboBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(219)),
				static_cast<System::Int32>(static_cast<System::Byte>(219)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"datasource=localhost; username=root; password=password; database=ESR_DB" });
			this->comboBox2->Location = System::Drawing::Point(6, 43);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(395, 24);
			this->comboBox2->TabIndex = 14;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->comboBox2);
			this->groupBox3->Controls->Add(this->ConnectDBButton);
			this->groupBox3->Controls->Add(this->cbConnection);
			this->groupBox3->Location = System::Drawing::Point(384, 12);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(407, 172);
			this->groupBox3->TabIndex = 15;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Conexión";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 24);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(97, 16);
			this->label3->TabIndex = 15;
			this->label3->Text = L"Base de Datos";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->button1);
			this->groupBox6->Controls->Add(this->editCheckBox);
			this->groupBox6->Controls->Add(this->cambiosLabel);
			this->groupBox6->Location = System::Drawing::Point(1425, 12);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(343, 178);
			this->groupBox6->TabIndex = 16;
			this->groupBox6->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(219)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(229)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1780, 814);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->HelpButton = true;
			this->Name = L"Form1";
			this->Text = L"Visor de Base de Datos";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DBView))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
		   

	private: System::Void botonIngreso_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string usuario = "usuario";
		std::string contrasenia = "contraseña";
		if (systemString2std(tbUsuario->Text) == usuario && systemString2std(tbContraseña->Text) == contrasenia) {
			logIn = true;
			this->lbErrorLogIn->Text = "";
			cbConnection->SetItemChecked(1, true);
			tbUsuario->Text = "";
			tbContraseña->Text = "";
		}
		else {
			logIn = false;
			this->lbErrorLogIn->ForeColor = System::Drawing::Color::Red;
			this->lbErrorLogIn->Text = "Usuario o Contraseña incorrecto";
			cbConnection->SetItemChecked(1, false);
			lbColumns->Items->Clear();
		}

	}
			private: static std::string systemString2std(System::String^ string) {
			   using System::Runtime::InteropServices::Marshal;
			   System::IntPtr pointer = Marshal::StringToHGlobalAnsi(string);
			   char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
			   std::string returnString(charPointer, string->Length);
			   Marshal::FreeHGlobal(pointer);
			   return returnString;
			}
			private: static String^ std2systemString(std::string str){
				return gcnew String(str.c_str());
			}

private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void lbColumns_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void cbTables_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	lbColumns->Items->Clear();
	fillColumns();

}

	   private: bool checkLogIn() {
		   if (tbUsuario->Text == usuario && tbContraseña->Text == contrasenia) {
			   return true;
		   }
		   else {
			   return false;
		   }
	   }
private:
	System::Data::DataTable^ dataTable = gcnew System::Data::DataTable();
private: System::Void dataGridView1_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
}
private: System::Void bAceptar_Click(System::Object^ sender, System::EventArgs^ e) {
	if (logIn && lbColumns->SelectedIndex >= 0) {
		if (DBView->RowCount == 0) {
			LoadDataFromDB(lbColumns->SelectedItem->ToString(), cbTables->SelectedItem->ToString());
			cambiosLabel->Text = "SIN CAMBIOS";
			cambiosLabel->ForeColor = Color::Black;

		}
		else if (DBView->RowCount > 0 && ! dataChanged) {
			LoadDataFromDB(lbColumns->SelectedItem->ToString(), cbTables->SelectedItem->ToString());
			cambiosLabel->Text = "SIN CAMBIOS";
			cambiosLabel->ForeColor = Color::Black;
		}
		
		
		
	}
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void cbConnection_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void groupBox4_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void bClearDBView_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!dataChanged || ableToDelete) {
		DBView->Columns->Clear();
		dataChanged = false;
		ableToDelete = false;
	}
	
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	
	
	
	//dataTable->DefaultView->RowFilter = System::String::Format("[{0}] LIKE '%{1}%'", columnas[0]->ColumnName, textBox1->Text);
}
private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	if (! dataChanged) {
		textBox1->Text = "";
		comboBox1->Text = "";
		LoadDataFromDB(lbColumns->SelectedItem->ToString(), cbTables->SelectedItem->ToString());
	}

}
private: System::Void ConnectDBButton_Click(System::Object^ sender, System::EventArgs^ e) {
	//System::String^ connectionString = connectionTB->Text->ToString();
	//MySqlConnection^ conn = gcnew MySqlConnection(connectionString);
	if (logIn) {
		connectDataBase();
	}
	
	
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	fillColumns();
}
private: System::Void DBView_CellBeginEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs^ e) {
}
private: System::Void DBView_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
	Tuple<int, int>^ cellKey = Tuple::Create(e->RowIndex, e->ColumnIndex);
	modifiedCells->Add(cellKey);
	DBView->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Style->BackColor = Color::Yellow;
	dataChanged = true;
	cambiosLabel->Text = "CAMBIOS SIN GUARDAR";
	cambiosLabel->ForeColor = Color::Red;
	
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	MySqlConnection^ conn = gcnew MySqlConnection(comboBox2->Text->ToString());
	List<Tuple<int, int>^>^ errorCells = gcnew List<Tuple<int, int>^>();
	try {
		conn->Open();
		cbConnection->SetItemChecked(0, true);

		if (DBView->Rows->Count == dataTableCopy->Rows->Count) {
			for (unsigned int i = 0; i < modifiedCells->Count; i++) {
				if (systemString2std(lbColumns->SelectedItem->ToString()) == "Todo") {
					MySqlDataAdapter^ adapter = gcnew MySqlDataAdapter("SELECT * FROM " + cbTables->Text->ToString(), conn);
					MySqlCommand^ commandShowKeys = gcnew MySqlCommand("SHOW KEYS FROM " + cbTables->Text->ToString() + " WHERE Key_name = 'PRIMARY';", conn);
					MySqlDataReader^ readerShowKeys = commandShowKeys->ExecuteReader();
					UInt32 primaryKeyIndex;
					while (readerShowKeys->Read()) {
						primaryKeyIndex = safe_cast<UInt32>(readerShowKeys["Seq_in_index"]) - 1;
					}
					readerShowKeys->Close();
					//Si borra el valor de la llave primaria, eliminar la fila
					//Lógica para añadir filas
					/*Comparar el numero de filas del dataTable que es el source del DataGridView con la copia que se hace cada vez que se llama a la base de datos
					deespués iterar las filas extra (añadidas) y poner el comando insert (Para no delimitar que deban poner todos los valores de la fila iterar también
					las columnas que no tengan un valor nulo en la fila para así obtener sus nombres y añadirlos en el query) "INSERT INTO nuevasTablas[columna]->nombre VALUES (nuevasCeldas->Value)"*/
					MySqlCommand^ commandUpdate = gcnew MySqlCommand("UPDATE " + cbTables->Text->ToString() + " SET " + DBView->Columns[modifiedCells[i]->Item2]->Name->ToString() + " = " + " ' " + DBView->Rows[modifiedCells[i]->Item1]->Cells[modifiedCells[i]->Item2]->Value + " ' " + " WHERE " + DBView->Columns[primaryKeyIndex]->Name->ToString() + " = " + DBView->Rows[modifiedCells[i]->Item1]->Cells[primaryKeyIndex]->Value + " ; ", conn);
					DBView->Rows[modifiedCells[i]->Item1]->Cells[modifiedCells[i]->Item2]->Style->BackColor = Color::LightGreen;
					commandUpdate->ExecuteNonQuery();

				}
				else {
				}
			}
			cambiosLabel->Text = "CAMBIOS GUARDADOS";
			cambiosLabel->ForeColor = Color::Green;
			DBView->BackColor = Color::White;
			dataChanged = false;
			modifiedCells->Clear();
		}
		//Si el numero de filas del DBView es mayor al de la tabla en la base de datos se llega a este punto
		else if (DBView->Rows->Count > dataTableCopy->Rows->Count)
		{
			MessageBox::Show("Se añadieron filas", "INFO", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}


	}
	catch (MySqlException^ ex) {
		for (unsigned int i = 0; i < modifiedCells->Count; i++) {
			DBView->Rows[modifiedCells[i]->Item1]->Cells[modifiedCells[i]->Item2]->Style->BackColor = Color::Red;
		}
		System::Windows::Forms::DialogResult result = MessageBox::Show("Error de MySQL: " + ex->Message + "\n" + "¿Desea descartar los cambios ? ", "Error / n ¿Desea descartar los cambios ? ", MessageBoxButtons::YesNo, MessageBoxIcon::Error);
		if (result == System::Windows::Forms::DialogResult::Yes) {
			for (unsigned int i = 0; i < modifiedCells->Count; i++) {
				DBView->Rows[modifiedCells[i]->Item1]->Cells[modifiedCells[i]->Item2]->Style->BackColor = Color::White;
			}
			modifiedCells->Clear();
		}

		ableToDelete = true;
	}
	catch (Exception^ ex) {
		MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	finally {
		conn->Close();

	}
}
private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (editCheckBox->Checked) {
		DBView->ReadOnly = false;
	}
	else {
		DBView->ReadOnly = true;
	}
}
private: System::Void button3_Click_1(System::Object^ sender, System::EventArgs^ e) {
	String^ url = "https://juanmanuelmurillo.github.io/DBManager-User-Guide/";
	System::Diagnostics::Process::Start(url);
}
private: System::Void comboBox1_SelectedIndexChanged_1(System::Object^ sender, System::EventArgs^ e) {
}
};

}

/*
FIN
Prometo no volver a hacer un código tan desordenado
y con tantas faltas a las convenciones en mi vida.
*/
