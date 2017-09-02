namespace 示波器上位机
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label12 = new System.Windows.Forms.Label();
            this.txtPower = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.txtVrms = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.txtVmin = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.txtVmax = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.txtVpp = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.txtDutyCycle = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.txtLowWidth = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.txtHighWidth = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.txtPriod = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtFeq = new System.Windows.Forms.TextBox();
            this.sp = new System.Windows.Forms.GroupBox();
            this.btnOpenSerialPort = new System.Windows.Forms.Button();
            this.cmbStreamCtrl = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.cmbCheckBit = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.cmbStopBit = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cmbDataBit = new System.Windows.Forms.ComboBox();
            this.cmbBaudRate = new System.Windows.Forms.ComboBox();
            this.cmbSerialPort = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
            this.toolStripStatusLabel5 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripProgressBar2 = new System.Windows.Forms.ToolStripProgressBar();
            this.toolStripStatusLabel4 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.btnStopRun = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.txbRevData = new System.Windows.Forms.TextBox();
            this.btnClearRevData = new System.Windows.Forms.Button();
            this.radioCharDisplay = new System.Windows.Forms.RadioButton();
            this.radioHexDisplay = new System.Windows.Forms.RadioButton();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.保存数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关闭ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开串口ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.控制ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sTOPToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.回显波形ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存波形ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.设置增益ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.增大ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.减小ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.自动ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.设置时基ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.增大ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.减小ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.自动ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.三角波ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.矩形波ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.正弦波ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.白噪声ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.自定义ToolStripMenuItem = new System.Windows.Forms.ToolStripSeparator();
            this.扫频ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripMenuItem();
            this.快速傅立叶分析ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.频谱分析ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.功率谱分析ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.交流分析ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.直流分析ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.版权信息ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.GainControl = new System.Windows.Forms.TabPage();
            this.btnSetGain = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label17 = new System.Windows.Forms.Label();
            this.btnAutoGain = new System.Windows.Forms.Button();
            this.button8 = new System.Windows.Forms.Button();
            this.button9 = new System.Windows.Forms.Button();
            this.TimeBaseControl = new System.Windows.Forms.TabPage();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.label29 = new System.Windows.Forms.Label();
            this.btnAutoTimeBase = new System.Windows.Forms.Button();
            this.btnSetTimeBase = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.button7 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.WaveGenerator = new System.Windows.Forms.TabPage();
            this.txtFGVpp = new System.Windows.Forms.ComboBox();
            this.label28 = new System.Windows.Forms.Label();
            this.txtFGDuty = new System.Windows.Forms.ComboBox();
            this.txtCurWave = new System.Windows.Forms.TextBox();
            this.txtFGFeq = new System.Windows.Forms.ComboBox();
            this.txtFGSwapTime = new System.Windows.Forms.TextBox();
            this.label27 = new System.Windows.Forms.Label();
            this.txtFGStopFeq = new System.Windows.Forms.TextBox();
            this.label26 = new System.Windows.Forms.Label();
            this.label25 = new System.Windows.Forms.Label();
            this.txtFGStartFeq = new System.Windows.Forms.TextBox();
            this.label24 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.btnSwapFeq = new System.Windows.Forms.Button();
            this.btnNoiseWave = new System.Windows.Forms.Button();
            this.btnSineWave = new System.Windows.Forms.Button();
            this.btnRectangularWave = new System.Windows.Forms.Button();
            this.btnTriangleWave = new System.Windows.Forms.Button();
            this.SignalAnalysis = new System.Windows.Forms.TabPage();
            this.button14 = new System.Windows.Forms.Button();
            this.button13 = new System.Windows.Forms.Button();
            this.button12 = new System.Windows.Forms.Button();
            this.button11 = new System.Windows.Forms.Button();
            this.button10 = new System.Windows.Forms.Button();
            this.OtherTable = new System.Windows.Forms.TabPage();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.sp.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.GainControl.SuspendLayout();
            this.TimeBaseControl.SuspendLayout();
            this.WaveGenerator.SuspendLayout();
            this.SignalAnalysis.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.pictureBox1);
            this.groupBox1.Controls.Add(this.label12);
            this.groupBox1.Controls.Add(this.txtPower);
            this.groupBox1.Controls.Add(this.label13);
            this.groupBox1.Controls.Add(this.txtVrms);
            this.groupBox1.Controls.Add(this.label14);
            this.groupBox1.Controls.Add(this.txtVmin);
            this.groupBox1.Controls.Add(this.label15);
            this.groupBox1.Controls.Add(this.txtVmax);
            this.groupBox1.Controls.Add(this.label16);
            this.groupBox1.Controls.Add(this.txtVpp);
            this.groupBox1.Controls.Add(this.label11);
            this.groupBox1.Controls.Add(this.txtDutyCycle);
            this.groupBox1.Controls.Add(this.label10);
            this.groupBox1.Controls.Add(this.txtLowWidth);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.txtHighWidth);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.txtPriod);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.txtFeq);
            this.groupBox1.Location = new System.Drawing.Point(12, 28);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(492, 172);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "波形数据";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(324, 11);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(162, 161);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 20;
            this.pictureBox1.TabStop = false;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(175, 134);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(71, 12);
            this.label12.TabIndex = 19;
            this.label12.Text = "CPU温度(℃)";
            // 
            // txtPower
            // 
            this.txtPower.Location = new System.Drawing.Point(246, 131);
            this.txtPower.Name = "txtPower";
            this.txtPower.Size = new System.Drawing.Size(72, 21);
            this.txtPower.TabIndex = 18;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(175, 104);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(59, 12);
            this.label13.TabIndex = 17;
            this.label13.Text = "有效值(V)";
            // 
            // txtVrms
            // 
            this.txtVrms.Location = new System.Drawing.Point(246, 101);
            this.txtVrms.Name = "txtVrms";
            this.txtVrms.Size = new System.Drawing.Size(72, 21);
            this.txtVrms.TabIndex = 16;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(175, 77);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(59, 12);
            this.label14.TabIndex = 15;
            this.label14.Text = "最小值(V)";
            // 
            // txtVmin
            // 
            this.txtVmin.Location = new System.Drawing.Point(246, 74);
            this.txtVmin.Name = "txtVmin";
            this.txtVmin.Size = new System.Drawing.Size(72, 21);
            this.txtVmin.TabIndex = 14;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(175, 50);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(59, 12);
            this.label15.TabIndex = 13;
            this.label15.Text = "最大值(V)";
            // 
            // txtVmax
            // 
            this.txtVmax.Location = new System.Drawing.Point(246, 47);
            this.txtVmax.Name = "txtVmax";
            this.txtVmax.Size = new System.Drawing.Size(72, 21);
            this.txtVmax.TabIndex = 12;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(175, 23);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(59, 12);
            this.label16.TabIndex = 11;
            this.label16.Text = "峰峰值(V)";
            // 
            // txtVpp
            // 
            this.txtVpp.Location = new System.Drawing.Point(246, 20);
            this.txtVpp.Name = "txtVpp";
            this.txtVpp.Size = new System.Drawing.Size(72, 21);
            this.txtVpp.TabIndex = 10;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(16, 134);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(59, 12);
            this.label11.TabIndex = 9;
            this.label11.Text = "占空比(%)";
            // 
            // txtDutyCycle
            // 
            this.txtDutyCycle.Location = new System.Drawing.Point(87, 131);
            this.txtDutyCycle.Name = "txtDutyCycle";
            this.txtDutyCycle.Size = new System.Drawing.Size(72, 21);
            this.txtDutyCycle.TabIndex = 8;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(16, 104);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(65, 12);
            this.label10.TabIndex = 7;
            this.label10.Text = "低电平(uS)";
            // 
            // txtLowWidth
            // 
            this.txtLowWidth.Location = new System.Drawing.Point(87, 101);
            this.txtLowWidth.Name = "txtLowWidth";
            this.txtLowWidth.Size = new System.Drawing.Size(72, 21);
            this.txtLowWidth.TabIndex = 6;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(16, 77);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(65, 12);
            this.label9.TabIndex = 5;
            this.label9.Text = "高电平(uS)";
            // 
            // txtHighWidth
            // 
            this.txtHighWidth.Location = new System.Drawing.Point(87, 74);
            this.txtHighWidth.Name = "txtHighWidth";
            this.txtHighWidth.Size = new System.Drawing.Size(72, 21);
            this.txtHighWidth.TabIndex = 4;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(16, 50);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 3;
            this.label8.Text = "周期(uS)";
            // 
            // txtPriod
            // 
            this.txtPriod.Location = new System.Drawing.Point(87, 47);
            this.txtPriod.Name = "txtPriod";
            this.txtPriod.Size = new System.Drawing.Size(72, 21);
            this.txtPriod.TabIndex = 2;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(16, 23);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 1;
            this.label7.Text = "频率(Hz)";
            // 
            // txtFeq
            // 
            this.txtFeq.Location = new System.Drawing.Point(87, 20);
            this.txtFeq.Name = "txtFeq";
            this.txtFeq.Size = new System.Drawing.Size(72, 21);
            this.txtFeq.TabIndex = 0;
            // 
            // sp
            // 
            this.sp.Controls.Add(this.btnOpenSerialPort);
            this.sp.Controls.Add(this.cmbStreamCtrl);
            this.sp.Controls.Add(this.label6);
            this.sp.Controls.Add(this.cmbCheckBit);
            this.sp.Controls.Add(this.label5);
            this.sp.Controls.Add(this.cmbStopBit);
            this.sp.Controls.Add(this.label4);
            this.sp.Controls.Add(this.cmbDataBit);
            this.sp.Controls.Add(this.cmbBaudRate);
            this.sp.Controls.Add(this.cmbSerialPort);
            this.sp.Controls.Add(this.label3);
            this.sp.Controls.Add(this.label2);
            this.sp.Controls.Add(this.label1);
            this.sp.Location = new System.Drawing.Point(12, 208);
            this.sp.Name = "sp";
            this.sp.Size = new System.Drawing.Size(227, 214);
            this.sp.TabIndex = 1;
            this.sp.TabStop = false;
            this.sp.Text = "串口设置";
            // 
            // btnOpenSerialPort
            // 
            this.btnOpenSerialPort.Location = new System.Drawing.Point(139, 90);
            this.btnOpenSerialPort.Name = "btnOpenSerialPort";
            this.btnOpenSerialPort.Size = new System.Drawing.Size(82, 52);
            this.btnOpenSerialPort.TabIndex = 12;
            this.btnOpenSerialPort.Text = "打开串口";
            this.btnOpenSerialPort.UseVisualStyleBackColor = true;
            this.btnOpenSerialPort.Click += new System.EventHandler(this.btnOpenSerialPort_Click);
            // 
            // cmbStreamCtrl
            // 
            this.cmbStreamCtrl.FormattingEnabled = true;
            this.cmbStreamCtrl.Items.AddRange(new object[] {
            "None",
            "Hardware",
            "Software"});
            this.cmbStreamCtrl.Location = new System.Drawing.Point(63, 183);
            this.cmbStreamCtrl.Name = "cmbStreamCtrl";
            this.cmbStreamCtrl.Size = new System.Drawing.Size(60, 20);
            this.cmbStreamCtrl.TabIndex = 11;
            this.cmbStreamCtrl.Text = "None";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(16, 186);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(29, 12);
            this.label6.TabIndex = 10;
            this.label6.Text = "流控";
            // 
            // cmbCheckBit
            // 
            this.cmbCheckBit.FormattingEnabled = true;
            this.cmbCheckBit.Items.AddRange(new object[] {
            "None",
            "Odd",
            "Even",
            "Mark",
            "Space"});
            this.cmbCheckBit.Location = new System.Drawing.Point(63, 152);
            this.cmbCheckBit.Name = "cmbCheckBit";
            this.cmbCheckBit.Size = new System.Drawing.Size(60, 20);
            this.cmbCheckBit.TabIndex = 9;
            this.cmbCheckBit.Text = "None";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(16, 155);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 12);
            this.label5.TabIndex = 8;
            this.label5.Text = "校验位";
            // 
            // cmbStopBit
            // 
            this.cmbStopBit.FormattingEnabled = true;
            this.cmbStopBit.Items.AddRange(new object[] {
            "1",
            "1.5",
            "2"});
            this.cmbStopBit.Location = new System.Drawing.Point(63, 122);
            this.cmbStopBit.Name = "cmbStopBit";
            this.cmbStopBit.Size = new System.Drawing.Size(60, 20);
            this.cmbStopBit.TabIndex = 7;
            this.cmbStopBit.Text = "1";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 125);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "停止位";
            // 
            // cmbDataBit
            // 
            this.cmbDataBit.FormattingEnabled = true;
            this.cmbDataBit.Items.AddRange(new object[] {
            "5",
            "6",
            "7",
            "8"});
            this.cmbDataBit.Location = new System.Drawing.Point(63, 90);
            this.cmbDataBit.Name = "cmbDataBit";
            this.cmbDataBit.Size = new System.Drawing.Size(60, 20);
            this.cmbDataBit.TabIndex = 5;
            this.cmbDataBit.Text = "8";
            // 
            // cmbBaudRate
            // 
            this.cmbBaudRate.FormattingEnabled = true;
            this.cmbBaudRate.Items.AddRange(new object[] {
            "2400",
            "4800",
            "9600",
            "14400",
            "19200",
            "38400",
            "115200",
            "128000"});
            this.cmbBaudRate.Location = new System.Drawing.Point(63, 55);
            this.cmbBaudRate.Name = "cmbBaudRate";
            this.cmbBaudRate.Size = new System.Drawing.Size(60, 20);
            this.cmbBaudRate.TabIndex = 4;
            this.cmbBaudRate.Text = "256000";
            // 
            // cmbSerialPort
            // 
            this.cmbSerialPort.FormattingEnabled = true;
            this.cmbSerialPort.Items.AddRange(new object[] {
            "COM1",
            "COM2",
            "COM3",
            "COM4",
            "COM5",
            "COM6",
            "COM7",
            "COM8",
            "COM9",
            "COM10",
            "COM11",
            "COM12",
            "COM13",
            "COM14",
            "COM15",
            "COM16",
            "COM17"});
            this.cmbSerialPort.Location = new System.Drawing.Point(63, 22);
            this.cmbSerialPort.Name = "cmbSerialPort";
            this.cmbSerialPort.Size = new System.Drawing.Size(60, 20);
            this.cmbSerialPort.TabIndex = 3;
            this.cmbSerialPort.Text = "COM2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(16, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 2;
            this.label3.Text = "数据位";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(16, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "波特率";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(16, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "串口号";
            // 
            // serialPort
            // 
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripProgressBar1,
            this.toolStripStatusLabel5,
            this.toolStripProgressBar2,
            this.toolStripStatusLabel4,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel3});
            this.statusStrip1.Location = new System.Drawing.Point(0, 425);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(836, 22);
            this.statusStrip1.TabIndex = 3;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(56, 17);
            this.toolStripStatusLabel1.Text = "CPU负载";
            // 
            // toolStripProgressBar1
            // 
            this.toolStripProgressBar1.Name = "toolStripProgressBar1";
            this.toolStripProgressBar1.Size = new System.Drawing.Size(100, 16);
            // 
            // toolStripStatusLabel5
            // 
            this.toolStripStatusLabel5.Name = "toolStripStatusLabel5";
            this.toolStripStatusLabel5.Size = new System.Drawing.Size(56, 17);
            this.toolStripStatusLabel5.Text = "内存使用";
            // 
            // toolStripProgressBar2
            // 
            this.toolStripProgressBar2.Name = "toolStripProgressBar2";
            this.toolStripProgressBar2.Size = new System.Drawing.Size(100, 16);
            // 
            // toolStripStatusLabel4
            // 
            this.toolStripStatusLabel4.Name = "toolStripStatusLabel4";
            this.toolStripStatusLabel4.Size = new System.Drawing.Size(61, 17);
            this.toolStripStatusLabel4.Text = "   版本1.1";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(64, 17);
            this.toolStripStatusLabel2.Text = "  版权信息";
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(157, 17);
            this.toolStripStatusLabel3.Text = "吴思远编写 2014年1月16日";
            // 
            // btnStopRun
            // 
            this.btnStopRun.Location = new System.Drawing.Point(6, 18);
            this.btnStopRun.Name = "btnStopRun";
            this.btnStopRun.Size = new System.Drawing.Size(61, 25);
            this.btnStopRun.TabIndex = 0;
            this.btnStopRun.Text = "STOP";
            this.btnStopRun.UseVisualStyleBackColor = true;
            this.btnStopRun.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(6, 46);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(61, 28);
            this.button2.TabIndex = 1;
            this.button2.Text = "回显波形";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(6, 80);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(61, 29);
            this.button3.TabIndex = 2;
            this.button3.Text = "保存波形";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.txbRevData);
            this.groupBox3.Controls.Add(this.btnClearRevData);
            this.groupBox3.Controls.Add(this.radioCharDisplay);
            this.groupBox3.Controls.Add(this.radioHexDisplay);
            this.groupBox3.Controls.Add(this.button5);
            this.groupBox3.Controls.Add(this.button4);
            this.groupBox3.Controls.Add(this.button1);
            this.groupBox3.Controls.Add(this.button3);
            this.groupBox3.Controls.Add(this.button2);
            this.groupBox3.Controls.Add(this.btnStopRun);
            this.groupBox3.Location = new System.Drawing.Point(245, 208);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(259, 214);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "调试终端";
            // 
            // txbRevData
            // 
            this.txbRevData.Location = new System.Drawing.Point(73, 18);
            this.txbRevData.Multiline = true;
            this.txbRevData.Name = "txbRevData";
            this.txbRevData.Size = new System.Drawing.Size(179, 153);
            this.txbRevData.TabIndex = 12;
            // 
            // btnClearRevData
            // 
            this.btnClearRevData.Location = new System.Drawing.Point(150, 173);
            this.btnClearRevData.Name = "btnClearRevData";
            this.btnClearRevData.Size = new System.Drawing.Size(74, 32);
            this.btnClearRevData.TabIndex = 11;
            this.btnClearRevData.Text = "清除显示";
            this.btnClearRevData.UseVisualStyleBackColor = true;
            this.btnClearRevData.Click += new System.EventHandler(this.btnClearRevData_Click);
            // 
            // radioCharDisplay
            // 
            this.radioCharDisplay.AutoSize = true;
            this.radioCharDisplay.Checked = true;
            this.radioCharDisplay.Location = new System.Drawing.Point(73, 171);
            this.radioCharDisplay.Name = "radioCharDisplay";
            this.radioCharDisplay.Size = new System.Drawing.Size(71, 16);
            this.radioCharDisplay.TabIndex = 10;
            this.radioCharDisplay.TabStop = true;
            this.radioCharDisplay.Text = "字符显示";
            this.radioCharDisplay.UseVisualStyleBackColor = true;
            // 
            // radioHexDisplay
            // 
            this.radioHexDisplay.AutoSize = true;
            this.radioHexDisplay.Location = new System.Drawing.Point(73, 189);
            this.radioHexDisplay.Name = "radioHexDisplay";
            this.radioHexDisplay.Size = new System.Drawing.Size(65, 16);
            this.radioHexDisplay.TabIndex = 9;
            this.radioHexDisplay.Text = "HEX显示";
            this.radioHexDisplay.UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(6, 180);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(61, 29);
            this.button5.TabIndex = 8;
            this.button5.Text = "IAP";
            this.button5.UseVisualStyleBackColor = true;
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(6, 147);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(61, 29);
            this.button4.TabIndex = 7;
            this.button4.Text = "直流耦合";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 115);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(61, 29);
            this.button1.TabIndex = 6;
            this.button1.Text = "交流耦合";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1,
            this.控制ToolStripMenuItem,
            this.toolStripMenuItem2,
            this.toolStripMenuItem3,
            this.toolStripMenuItem4,
            this.toolStripMenuItem5,
            this.帮助ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(836, 25);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.保存数据ToolStripMenuItem,
            this.关闭ToolStripMenuItem,
            this.打开串口ToolStripMenuItem});
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(44, 21);
            this.toolStripMenuItem1.Text = "文件";
            // 
            // 保存数据ToolStripMenuItem
            // 
            this.保存数据ToolStripMenuItem.Name = "保存数据ToolStripMenuItem";
            this.保存数据ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.保存数据ToolStripMenuItem.Text = "保存数据";
            // 
            // 关闭ToolStripMenuItem
            // 
            this.关闭ToolStripMenuItem.Name = "关闭ToolStripMenuItem";
            this.关闭ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.关闭ToolStripMenuItem.Text = "关闭串口";
            // 
            // 打开串口ToolStripMenuItem
            // 
            this.打开串口ToolStripMenuItem.Name = "打开串口ToolStripMenuItem";
            this.打开串口ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.打开串口ToolStripMenuItem.Text = "关闭程序";
            this.打开串口ToolStripMenuItem.Click += new System.EventHandler(this.打开串口ToolStripMenuItem_Click);
            // 
            // 控制ToolStripMenuItem
            // 
            this.控制ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sTOPToolStripMenuItem,
            this.回显波形ToolStripMenuItem,
            this.保存波形ToolStripMenuItem});
            this.控制ToolStripMenuItem.Name = "控制ToolStripMenuItem";
            this.控制ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.控制ToolStripMenuItem.Text = "控制";
            // 
            // sTOPToolStripMenuItem
            // 
            this.sTOPToolStripMenuItem.Name = "sTOPToolStripMenuItem";
            this.sTOPToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.sTOPToolStripMenuItem.Text = "STOP/RUN";
            this.sTOPToolStripMenuItem.Click += new System.EventHandler(this.sTOPToolStripMenuItem_Click);
            // 
            // 回显波形ToolStripMenuItem
            // 
            this.回显波形ToolStripMenuItem.Name = "回显波形ToolStripMenuItem";
            this.回显波形ToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.回显波形ToolStripMenuItem.Text = "回显波形";
            // 
            // 保存波形ToolStripMenuItem
            // 
            this.保存波形ToolStripMenuItem.Name = "保存波形ToolStripMenuItem";
            this.保存波形ToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.保存波形ToolStripMenuItem.Text = "保存波形";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.设置增益ToolStripMenuItem,
            this.增大ToolStripMenuItem,
            this.减小ToolStripMenuItem,
            this.toolStripSeparator2,
            this.自动ToolStripMenuItem});
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(68, 21);
            this.toolStripMenuItem2.Text = "增益控制";
            // 
            // 设置增益ToolStripMenuItem
            // 
            this.设置增益ToolStripMenuItem.Name = "设置增益ToolStripMenuItem";
            this.设置增益ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.设置增益ToolStripMenuItem.Text = "设置增益";
            // 
            // 增大ToolStripMenuItem
            // 
            this.增大ToolStripMenuItem.Name = "增大ToolStripMenuItem";
            this.增大ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.增大ToolStripMenuItem.Text = "增大";
            // 
            // 减小ToolStripMenuItem
            // 
            this.减小ToolStripMenuItem.Name = "减小ToolStripMenuItem";
            this.减小ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.减小ToolStripMenuItem.Text = "减小";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(121, 6);
            // 
            // 自动ToolStripMenuItem
            // 
            this.自动ToolStripMenuItem.Name = "自动ToolStripMenuItem";
            this.自动ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.自动ToolStripMenuItem.Text = "自动";
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.设置时基ToolStripMenuItem,
            this.增大ToolStripMenuItem1,
            this.减小ToolStripMenuItem1,
            this.toolStripSeparator1,
            this.自动ToolStripMenuItem1});
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(68, 21);
            this.toolStripMenuItem3.Text = "时基控制";
            // 
            // 设置时基ToolStripMenuItem
            // 
            this.设置时基ToolStripMenuItem.Name = "设置时基ToolStripMenuItem";
            this.设置时基ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.设置时基ToolStripMenuItem.Text = "设置时基";
            // 
            // 增大ToolStripMenuItem1
            // 
            this.增大ToolStripMenuItem1.Name = "增大ToolStripMenuItem1";
            this.增大ToolStripMenuItem1.Size = new System.Drawing.Size(124, 22);
            this.增大ToolStripMenuItem1.Text = "增大";
            // 
            // 减小ToolStripMenuItem1
            // 
            this.减小ToolStripMenuItem1.Name = "减小ToolStripMenuItem1";
            this.减小ToolStripMenuItem1.Size = new System.Drawing.Size(124, 22);
            this.减小ToolStripMenuItem1.Text = "减小";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(121, 6);
            // 
            // 自动ToolStripMenuItem1
            // 
            this.自动ToolStripMenuItem1.Name = "自动ToolStripMenuItem1";
            this.自动ToolStripMenuItem1.Size = new System.Drawing.Size(124, 22);
            this.自动ToolStripMenuItem1.Text = "自动";
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.三角波ToolStripMenuItem,
            this.矩形波ToolStripMenuItem,
            this.正弦波ToolStripMenuItem,
            this.白噪声ToolStripMenuItem,
            this.自定义ToolStripMenuItem,
            this.扫频ToolStripMenuItem});
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(80, 21);
            this.toolStripMenuItem4.Text = "信号发生器";
            // 
            // 三角波ToolStripMenuItem
            // 
            this.三角波ToolStripMenuItem.Name = "三角波ToolStripMenuItem";
            this.三角波ToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.三角波ToolStripMenuItem.Text = "三角波";
            // 
            // 矩形波ToolStripMenuItem
            // 
            this.矩形波ToolStripMenuItem.Name = "矩形波ToolStripMenuItem";
            this.矩形波ToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.矩形波ToolStripMenuItem.Text = "矩形波";
            // 
            // 正弦波ToolStripMenuItem
            // 
            this.正弦波ToolStripMenuItem.Name = "正弦波ToolStripMenuItem";
            this.正弦波ToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.正弦波ToolStripMenuItem.Text = "正弦波";
            // 
            // 白噪声ToolStripMenuItem
            // 
            this.白噪声ToolStripMenuItem.Name = "白噪声ToolStripMenuItem";
            this.白噪声ToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.白噪声ToolStripMenuItem.Text = "白噪声";
            // 
            // 自定义ToolStripMenuItem
            // 
            this.自定义ToolStripMenuItem.Name = "自定义ToolStripMenuItem";
            this.自定义ToolStripMenuItem.Size = new System.Drawing.Size(109, 6);
            // 
            // 扫频ToolStripMenuItem
            // 
            this.扫频ToolStripMenuItem.Name = "扫频ToolStripMenuItem";
            this.扫频ToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.扫频ToolStripMenuItem.Text = "扫频";
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.快速傅立叶分析ToolStripMenuItem,
            this.频谱分析ToolStripMenuItem,
            this.功率谱分析ToolStripMenuItem,
            this.交流分析ToolStripMenuItem,
            this.直流分析ToolStripMenuItem});
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(68, 21);
            this.toolStripMenuItem5.Text = "信号分析";
            // 
            // 快速傅立叶分析ToolStripMenuItem
            // 
            this.快速傅立叶分析ToolStripMenuItem.Name = "快速傅立叶分析ToolStripMenuItem";
            this.快速傅立叶分析ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.快速傅立叶分析ToolStripMenuItem.Text = "快速傅立叶分析";
            // 
            // 频谱分析ToolStripMenuItem
            // 
            this.频谱分析ToolStripMenuItem.Name = "频谱分析ToolStripMenuItem";
            this.频谱分析ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.频谱分析ToolStripMenuItem.Text = "频谱分析";
            // 
            // 功率谱分析ToolStripMenuItem
            // 
            this.功率谱分析ToolStripMenuItem.Name = "功率谱分析ToolStripMenuItem";
            this.功率谱分析ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.功率谱分析ToolStripMenuItem.Text = "功率谱分析";
            // 
            // 交流分析ToolStripMenuItem
            // 
            this.交流分析ToolStripMenuItem.Name = "交流分析ToolStripMenuItem";
            this.交流分析ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.交流分析ToolStripMenuItem.Text = "交流分析";
            // 
            // 直流分析ToolStripMenuItem
            // 
            this.直流分析ToolStripMenuItem.Name = "直流分析ToolStripMenuItem";
            this.直流分析ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.直流分析ToolStripMenuItem.Text = "直流分析";
            // 
            // 帮助ToolStripMenuItem
            // 
            this.帮助ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.版权信息ToolStripMenuItem});
            this.帮助ToolStripMenuItem.Name = "帮助ToolStripMenuItem";
            this.帮助ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.帮助ToolStripMenuItem.Text = "帮助";
            // 
            // 版权信息ToolStripMenuItem
            // 
            this.版权信息ToolStripMenuItem.Name = "版权信息ToolStripMenuItem";
            this.版权信息ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.版权信息ToolStripMenuItem.Text = "版权信息";
            this.版权信息ToolStripMenuItem.Click += new System.EventHandler(this.版权信息ToolStripMenuItem_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.GainControl);
            this.tabControl1.Controls.Add(this.TimeBaseControl);
            this.tabControl1.Controls.Add(this.WaveGenerator);
            this.tabControl1.Controls.Add(this.SignalAnalysis);
            this.tabControl1.Controls.Add(this.OtherTable);
            this.tabControl1.Location = new System.Drawing.Point(6, 18);
            this.tabControl1.Multiline = true;
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(315, 191);
            this.tabControl1.TabIndex = 5;
            // 
            // GainControl
            // 
            this.GainControl.BackColor = System.Drawing.SystemColors.Menu;
            this.GainControl.Controls.Add(this.btnSetGain);
            this.GainControl.Controls.Add(this.comboBox1);
            this.GainControl.Controls.Add(this.label17);
            this.GainControl.Controls.Add(this.btnAutoGain);
            this.GainControl.Controls.Add(this.button8);
            this.GainControl.Controls.Add(this.button9);
            this.GainControl.Location = new System.Drawing.Point(4, 22);
            this.GainControl.Name = "GainControl";
            this.GainControl.Padding = new System.Windows.Forms.Padding(3);
            this.GainControl.Size = new System.Drawing.Size(307, 165);
            this.GainControl.TabIndex = 0;
            this.GainControl.Text = "增益控制";
            // 
            // btnSetGain
            // 
            this.btnSetGain.Location = new System.Drawing.Point(223, 66);
            this.btnSetGain.Name = "btnSetGain";
            this.btnSetGain.Size = new System.Drawing.Size(61, 35);
            this.btnSetGain.TabIndex = 24;
            this.btnSetGain.Text = "设置增益";
            this.btnSetGain.UseVisualStyleBackColor = true;
            this.btnSetGain.Click += new System.EventHandler(this.btnSetGain_Click);
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "X0.05",
            "X0.1",
            "X1",
            "X2",
            "X4",
            "X5",
            "X10",
            "X25"});
            this.comboBox1.Location = new System.Drawing.Point(157, 75);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(60, 20);
            this.comboBox1.TabIndex = 23;
            this.comboBox1.Text = "X1";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(98, 78);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(53, 12);
            this.label17.TabIndex = 22;
            this.label17.Text = "设置增益";
            // 
            // btnAutoGain
            // 
            this.btnAutoGain.Location = new System.Drawing.Point(16, 18);
            this.btnAutoGain.Name = "btnAutoGain";
            this.btnAutoGain.Size = new System.Drawing.Size(61, 37);
            this.btnAutoGain.TabIndex = 6;
            this.btnAutoGain.Text = "自动增益";
            this.btnAutoGain.UseVisualStyleBackColor = true;
            this.btnAutoGain.Click += new System.EventHandler(this.btnAutoGain_Click);
            // 
            // button8
            // 
            this.button8.Location = new System.Drawing.Point(17, 112);
            this.button8.Name = "button8";
            this.button8.Size = new System.Drawing.Size(61, 37);
            this.button8.TabIndex = 4;
            this.button8.Text = "减";
            this.button8.UseVisualStyleBackColor = true;
            this.button8.Click += new System.EventHandler(this.button8_Click);
            // 
            // button9
            // 
            this.button9.Location = new System.Drawing.Point(17, 65);
            this.button9.Name = "button9";
            this.button9.Size = new System.Drawing.Size(60, 37);
            this.button9.TabIndex = 3;
            this.button9.Text = "加";
            this.button9.UseVisualStyleBackColor = true;
            this.button9.Click += new System.EventHandler(this.button9_Click);
            // 
            // TimeBaseControl
            // 
            this.TimeBaseControl.BackColor = System.Drawing.SystemColors.Menu;
            this.TimeBaseControl.Controls.Add(this.comboBox2);
            this.TimeBaseControl.Controls.Add(this.label29);
            this.TimeBaseControl.Controls.Add(this.btnAutoTimeBase);
            this.TimeBaseControl.Controls.Add(this.btnSetTimeBase);
            this.TimeBaseControl.Controls.Add(this.progressBar1);
            this.TimeBaseControl.Controls.Add(this.button7);
            this.TimeBaseControl.Controls.Add(this.button6);
            this.TimeBaseControl.Location = new System.Drawing.Point(4, 22);
            this.TimeBaseControl.Name = "TimeBaseControl";
            this.TimeBaseControl.Padding = new System.Windows.Forms.Padding(3);
            this.TimeBaseControl.Size = new System.Drawing.Size(307, 165);
            this.TimeBaseControl.TabIndex = 1;
            this.TimeBaseControl.Text = "时基控制";
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "1",
            "2",
            "5",
            "10",
            "15",
            "20",
            "30",
            "40",
            "50",
            "60",
            "70",
            "80",
            "90",
            "100",
            "200",
            "500",
            "1000"});
            this.comboBox2.Location = new System.Drawing.Point(157, 75);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(60, 20);
            this.comboBox2.TabIndex = 28;
            this.comboBox2.Text = "99";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(98, 78);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(53, 12);
            this.label29.TabIndex = 27;
            this.label29.Text = "设置时基";
            // 
            // btnAutoTimeBase
            // 
            this.btnAutoTimeBase.Location = new System.Drawing.Point(17, 18);
            this.btnAutoTimeBase.Name = "btnAutoTimeBase";
            this.btnAutoTimeBase.Size = new System.Drawing.Size(61, 35);
            this.btnAutoTimeBase.TabIndex = 26;
            this.btnAutoTimeBase.Text = "自动时基";
            this.btnAutoTimeBase.UseVisualStyleBackColor = true;
            this.btnAutoTimeBase.Click += new System.EventHandler(this.btnAutoTimeBase_Click);
            // 
            // btnSetTimeBase
            // 
            this.btnSetTimeBase.Location = new System.Drawing.Point(223, 67);
            this.btnSetTimeBase.Name = "btnSetTimeBase";
            this.btnSetTimeBase.Size = new System.Drawing.Size(61, 35);
            this.btnSetTimeBase.TabIndex = 25;
            this.btnSetTimeBase.Text = "设置时基";
            this.btnSetTimeBase.UseVisualStyleBackColor = true;
            this.btnSetTimeBase.Click += new System.EventHandler(this.btnSetTimeBase_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(220, 140);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(81, 18);
            this.progressBar1.Step = 2;
            this.progressBar1.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            this.progressBar1.TabIndex = 2;
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(17, 112);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(61, 37);
            this.button7.TabIndex = 1;
            this.button7.Text = "减";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(17, 67);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(61, 35);
            this.button6.TabIndex = 0;
            this.button6.Text = "加";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // WaveGenerator
            // 
            this.WaveGenerator.BackColor = System.Drawing.SystemColors.Menu;
            this.WaveGenerator.Controls.Add(this.txtFGVpp);
            this.WaveGenerator.Controls.Add(this.label28);
            this.WaveGenerator.Controls.Add(this.txtFGDuty);
            this.WaveGenerator.Controls.Add(this.txtCurWave);
            this.WaveGenerator.Controls.Add(this.txtFGFeq);
            this.WaveGenerator.Controls.Add(this.txtFGSwapTime);
            this.WaveGenerator.Controls.Add(this.label27);
            this.WaveGenerator.Controls.Add(this.txtFGStopFeq);
            this.WaveGenerator.Controls.Add(this.label26);
            this.WaveGenerator.Controls.Add(this.label25);
            this.WaveGenerator.Controls.Add(this.txtFGStartFeq);
            this.WaveGenerator.Controls.Add(this.label24);
            this.WaveGenerator.Controls.Add(this.label23);
            this.WaveGenerator.Controls.Add(this.label22);
            this.WaveGenerator.Controls.Add(this.btnSwapFeq);
            this.WaveGenerator.Controls.Add(this.btnNoiseWave);
            this.WaveGenerator.Controls.Add(this.btnSineWave);
            this.WaveGenerator.Controls.Add(this.btnRectangularWave);
            this.WaveGenerator.Controls.Add(this.btnTriangleWave);
            this.WaveGenerator.Location = new System.Drawing.Point(4, 22);
            this.WaveGenerator.Name = "WaveGenerator";
            this.WaveGenerator.Padding = new System.Windows.Forms.Padding(3);
            this.WaveGenerator.Size = new System.Drawing.Size(307, 165);
            this.WaveGenerator.TabIndex = 2;
            this.WaveGenerator.Text = "信号发生器";
            // 
            // txtFGVpp
            // 
            this.txtFGVpp.FormattingEnabled = true;
            this.txtFGVpp.Items.AddRange(new object[] {
            "0.5",
            "1.0",
            "1.5",
            "2.0",
            "2.5",
            "3.0",
            "3.3"});
            this.txtFGVpp.Location = new System.Drawing.Point(77, 67);
            this.txtFGVpp.Name = "txtFGVpp";
            this.txtFGVpp.Size = new System.Drawing.Size(60, 20);
            this.txtFGVpp.TabIndex = 13;
            this.txtFGVpp.Text = "3.0";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(153, 40);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(53, 12);
            this.label28.TabIndex = 43;
            this.label28.Text = "当前波形";
            // 
            // txtFGDuty
            // 
            this.txtFGDuty.FormattingEnabled = true;
            this.txtFGDuty.Items.AddRange(new object[] {
            "10",
            "20",
            "30",
            "40",
            "50",
            "60",
            "70",
            "80",
            "90"});
            this.txtFGDuty.Location = new System.Drawing.Point(77, 38);
            this.txtFGDuty.Name = "txtFGDuty";
            this.txtFGDuty.Size = new System.Drawing.Size(60, 20);
            this.txtFGDuty.TabIndex = 12;
            this.txtFGDuty.Text = "50";
            // 
            // txtCurWave
            // 
            this.txtCurWave.Location = new System.Drawing.Point(155, 58);
            this.txtCurWave.Name = "txtCurWave";
            this.txtCurWave.Size = new System.Drawing.Size(50, 21);
            this.txtCurWave.TabIndex = 42;
            // 
            // txtFGFeq
            // 
            this.txtFGFeq.FormattingEnabled = true;
            this.txtFGFeq.Items.AddRange(new object[] {
            "1000",
            "1200",
            "1400",
            "1600",
            "1800",
            "2000",
            "2500",
            "3000",
            "3500",
            "4000",
            "4500",
            "5000",
            "5500",
            "6000",
            "6500",
            "7000",
            "7500",
            "8000",
            "8500",
            "9000",
            "9500",
            "10000"});
            this.txtFGFeq.Location = new System.Drawing.Point(77, 10);
            this.txtFGFeq.Name = "txtFGFeq";
            this.txtFGFeq.Size = new System.Drawing.Size(60, 20);
            this.txtFGFeq.TabIndex = 11;
            this.txtFGFeq.Text = "3000";
            // 
            // txtFGSwapTime
            // 
            this.txtFGSwapTime.Location = new System.Drawing.Point(124, 115);
            this.txtFGSwapTime.Name = "txtFGSwapTime";
            this.txtFGSwapTime.Size = new System.Drawing.Size(53, 21);
            this.txtFGSwapTime.TabIndex = 41;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(124, 97);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(53, 12);
            this.label27.TabIndex = 40;
            this.label27.Text = "扫描时间";
            // 
            // txtFGStopFeq
            // 
            this.txtFGStopFeq.Location = new System.Drawing.Point(65, 115);
            this.txtFGStopFeq.Name = "txtFGStopFeq";
            this.txtFGStopFeq.Size = new System.Drawing.Size(53, 21);
            this.txtFGStopFeq.TabIndex = 39;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(65, 97);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(53, 12);
            this.label26.TabIndex = 38;
            this.label26.Text = "截止频率";
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(6, 97);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(53, 12);
            this.label25.TabIndex = 36;
            this.label25.Text = "起始频率";
            // 
            // txtFGStartFeq
            // 
            this.txtFGStartFeq.Location = new System.Drawing.Point(6, 115);
            this.txtFGStartFeq.Name = "txtFGStartFeq";
            this.txtFGStartFeq.Size = new System.Drawing.Size(53, 21);
            this.txtFGStartFeq.TabIndex = 35;
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(6, 70);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(59, 12);
            this.label24.TabIndex = 34;
            this.label24.Text = "峰峰值(V)";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(6, 41);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(59, 12);
            this.label23.TabIndex = 32;
            this.label23.Text = "占空比(%)";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(6, 14);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(53, 12);
            this.label22.TabIndex = 22;
            this.label22.Text = "频率(Hz)";
            // 
            // btnSwapFeq
            // 
            this.btnSwapFeq.Location = new System.Drawing.Point(8, 141);
            this.btnSwapFeq.Name = "btnSwapFeq";
            this.btnSwapFeq.Size = new System.Drawing.Size(169, 21);
            this.btnSwapFeq.TabIndex = 30;
            this.btnSwapFeq.Text = "开始扫频";
            this.btnSwapFeq.UseVisualStyleBackColor = true;
            this.btnSwapFeq.Click += new System.EventHandler(this.btnSwapFeq_Click);
            // 
            // btnNoiseWave
            // 
            this.btnNoiseWave.Location = new System.Drawing.Point(231, 122);
            this.btnNoiseWave.Name = "btnNoiseWave";
            this.btnNoiseWave.Size = new System.Drawing.Size(61, 35);
            this.btnNoiseWave.TabIndex = 29;
            this.btnNoiseWave.Text = "白噪声";
            this.btnNoiseWave.UseVisualStyleBackColor = true;
            this.btnNoiseWave.Click += new System.EventHandler(this.btnNoiseWave_Click);
            // 
            // btnSineWave
            // 
            this.btnSineWave.Location = new System.Drawing.Point(231, 82);
            this.btnSineWave.Name = "btnSineWave";
            this.btnSineWave.Size = new System.Drawing.Size(61, 35);
            this.btnSineWave.TabIndex = 28;
            this.btnSineWave.Text = "正弦波";
            this.btnSineWave.UseVisualStyleBackColor = true;
            this.btnSineWave.Click += new System.EventHandler(this.btnSineWave_Click);
            // 
            // btnRectangularWave
            // 
            this.btnRectangularWave.Location = new System.Drawing.Point(231, 44);
            this.btnRectangularWave.Name = "btnRectangularWave";
            this.btnRectangularWave.Size = new System.Drawing.Size(61, 35);
            this.btnRectangularWave.TabIndex = 27;
            this.btnRectangularWave.Text = "矩形波";
            this.btnRectangularWave.UseVisualStyleBackColor = true;
            this.btnRectangularWave.Click += new System.EventHandler(this.btnRectangularWave_Click);
            // 
            // btnTriangleWave
            // 
            this.btnTriangleWave.Location = new System.Drawing.Point(231, 7);
            this.btnTriangleWave.Name = "btnTriangleWave";
            this.btnTriangleWave.Size = new System.Drawing.Size(61, 35);
            this.btnTriangleWave.TabIndex = 26;
            this.btnTriangleWave.Text = "三角波";
            this.btnTriangleWave.UseVisualStyleBackColor = true;
            this.btnTriangleWave.Click += new System.EventHandler(this.btnTriangleWave_Click);
            // 
            // SignalAnalysis
            // 
            this.SignalAnalysis.BackColor = System.Drawing.SystemColors.Menu;
            this.SignalAnalysis.Controls.Add(this.button14);
            this.SignalAnalysis.Controls.Add(this.button13);
            this.SignalAnalysis.Controls.Add(this.button12);
            this.SignalAnalysis.Controls.Add(this.button11);
            this.SignalAnalysis.Controls.Add(this.button10);
            this.SignalAnalysis.Location = new System.Drawing.Point(4, 22);
            this.SignalAnalysis.Name = "SignalAnalysis";
            this.SignalAnalysis.Padding = new System.Windows.Forms.Padding(3);
            this.SignalAnalysis.Size = new System.Drawing.Size(307, 165);
            this.SignalAnalysis.TabIndex = 3;
            this.SignalAnalysis.Text = "信号分析";
            // 
            // button14
            // 
            this.button14.Location = new System.Drawing.Point(97, 62);
            this.button14.Name = "button14";
            this.button14.Size = new System.Drawing.Size(61, 35);
            this.button14.TabIndex = 31;
            this.button14.Text = "DC分析";
            this.button14.UseVisualStyleBackColor = true;
            this.button14.Click += new System.EventHandler(this.button14_Click);
            // 
            // button13
            // 
            this.button13.Location = new System.Drawing.Point(97, 18);
            this.button13.Name = "button13";
            this.button13.Size = new System.Drawing.Size(61, 35);
            this.button13.TabIndex = 30;
            this.button13.Text = "AC分析";
            this.button13.UseVisualStyleBackColor = true;
            this.button13.Click += new System.EventHandler(this.button13_Click);
            // 
            // button12
            // 
            this.button12.Location = new System.Drawing.Point(15, 107);
            this.button12.Name = "button12";
            this.button12.Size = new System.Drawing.Size(76, 35);
            this.button12.TabIndex = 29;
            this.button12.Text = "功率谱分析";
            this.button12.UseVisualStyleBackColor = true;
            this.button12.Click += new System.EventHandler(this.button12_Click);
            // 
            // button11
            // 
            this.button11.Location = new System.Drawing.Point(15, 62);
            this.button11.Name = "button11";
            this.button11.Size = new System.Drawing.Size(76, 35);
            this.button11.TabIndex = 28;
            this.button11.Text = "频谱分析";
            this.button11.UseVisualStyleBackColor = true;
            this.button11.Click += new System.EventHandler(this.button11_Click);
            // 
            // button10
            // 
            this.button10.Location = new System.Drawing.Point(15, 18);
            this.button10.Name = "button10";
            this.button10.Size = new System.Drawing.Size(76, 35);
            this.button10.TabIndex = 27;
            this.button10.Text = "傅立叶分析";
            this.button10.UseVisualStyleBackColor = true;
            this.button10.Click += new System.EventHandler(this.button10_Click);
            // 
            // OtherTable
            // 
            this.OtherTable.BackColor = System.Drawing.SystemColors.Menu;
            this.OtherTable.Location = new System.Drawing.Point(4, 22);
            this.OtherTable.Name = "OtherTable";
            this.OtherTable.Padding = new System.Windows.Forms.Padding(3);
            this.OtherTable.Size = new System.Drawing.Size(307, 165);
            this.OtherTable.TabIndex = 4;
            this.OtherTable.Text = "其他";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tabControl1);
            this.groupBox2.Location = new System.Drawing.Point(510, 208);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(325, 217);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "控制台";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("宋体", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label18.Location = new System.Drawing.Point(29, 20);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(250, 24);
            this.label18.TabIndex = 7;
            this.label18.Text = "STM32低频数字示波器";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label19.Location = new System.Drawing.Point(100, 50);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(120, 21);
            this.label19.TabIndex = 8;
            this.label19.Text = "信号发生器";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label20.Location = new System.Drawing.Point(101, 86);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(120, 21);
            this.label20.TabIndex = 9;
            this.label20.Text = "信号分析仪";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Font = new System.Drawing.Font("宋体", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label21.Location = new System.Drawing.Point(77, 125);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(168, 21);
            this.label21.TabIndex = 10;
            this.label21.Text = "控制台软件V1.1";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label21);
            this.groupBox4.Controls.Add(this.label20);
            this.groupBox4.Controls.Add(this.label19);
            this.groupBox4.Controls.Add(this.label18);
            this.groupBox4.Location = new System.Drawing.Point(516, 28);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(314, 171);
            this.groupBox4.TabIndex = 11;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "信息栏";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(836, 447);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.sp);
            this.Controls.Add(this.groupBox1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "STM32示波器控制端";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.sp.ResumeLayout(false);
            this.sp.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.GainControl.ResumeLayout(false);
            this.GainControl.PerformLayout();
            this.TimeBaseControl.ResumeLayout(false);
            this.TimeBaseControl.PerformLayout();
            this.WaveGenerator.ResumeLayout(false);
            this.WaveGenerator.PerformLayout();
            this.SignalAnalysis.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox sp;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cmbDataBit;
        private System.Windows.Forms.ComboBox cmbBaudRate;
        private System.Windows.Forms.ComboBox cmbSerialPort;
        private System.Windows.Forms.ComboBox cmbCheckBit;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cmbStopBit;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cmbStreamCtrl;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btnOpenSerialPort;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox txtFeq;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtDutyCycle;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtLowWidth;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txtHighWidth;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtPriod;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox txtPower;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox txtVrms;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox txtVmin;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox txtVmax;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox txtVpp;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel4;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button btnStopRun;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 保存数据ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关闭ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开串口ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 控制ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem sTOPToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 回显波形ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存波形ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 帮助ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 版权信息ToolStripMenuItem;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.RadioButton radioCharDisplay;
        private System.Windows.Forms.RadioButton radioHexDisplay;
        private System.Windows.Forms.Button btnClearRevData;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage GainControl;
        private System.Windows.Forms.TabPage TimeBaseControl;
        private System.Windows.Forms.TabPage WaveGenerator;
        private System.Windows.Forms.TabPage SignalAnalysis;
        private System.Windows.Forms.TabPage OtherTable;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem 设置增益ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 增大ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 减小ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 自动ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem 设置时基ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 增大ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 减小ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 自动ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem5;
        private System.Windows.Forms.ToolStripMenuItem 三角波ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 矩形波ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 正弦波ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 白噪声ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator 自定义ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 扫频ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 快速傅立叶分析ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 频谱分析ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 功率谱分析ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 交流分析ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 直流分析ToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button button7;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Button button8;
        private System.Windows.Forms.Button button9;
        private System.Windows.Forms.Button btnAutoGain;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button btnSetGain;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel5;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar2;
        private System.Windows.Forms.Button btnAutoTimeBase;
        private System.Windows.Forms.Button btnSetTimeBase;
        private System.Windows.Forms.Button btnNoiseWave;
        private System.Windows.Forms.Button btnSineWave;
        private System.Windows.Forms.Button btnRectangularWave;
        private System.Windows.Forms.Button btnTriangleWave;
        private System.Windows.Forms.Button btnSwapFeq;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.TextBox txtFGSwapTime;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.TextBox txtFGStopFeq;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.TextBox txtFGStartFeq;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.TextBox txtCurWave;
        private System.Windows.Forms.Button button14;
        private System.Windows.Forms.Button button13;
        private System.Windows.Forms.Button button12;
        private System.Windows.Forms.Button button11;
        private System.Windows.Forms.Button button10;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.TextBox txbRevData;
        private System.Windows.Forms.ComboBox txtFGVpp;
        private System.Windows.Forms.ComboBox txtFGDuty;
        private System.Windows.Forms.ComboBox txtFGFeq;
    }
}

