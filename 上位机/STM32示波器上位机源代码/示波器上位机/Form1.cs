using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Runtime.InteropServices;


namespace 示波器上位机
{
    public partial class Form1 : Form
    {
        [DllImport("kernel32.dll")]
        static extern uint GetTickCount();
        static void Delay(uint ms)
        {
            uint start = GetTickCount();
            while (GetTickCount() - start < ms)
            {
                Application.DoEvents();
            }
        }
        public Form1()
        {
            InitializeComponent();
        }
        #region 已经设计好无需改动
        /*--------------------------------------------------------
                           打开串口按钮
       --------------------------------------------------------*/
        private void btnOpenSerialPort_Click(object sender, EventArgs e)  //打开关闭串口
        {
            string COM_Number = this.cmbSerialPort.Text;
            int BaudRate = Convert.ToInt32(this.cmbBaudRate.Text);
            int DataBit = Convert.ToInt32(this.cmbDataBit.Text);
            int StopBit = Convert.ToInt32(this.cmbStopBit.Text);

            if (!serialPort.IsOpen) //如果串口处于关闭状态
            {
                serialPort.PortName = COM_Number;  //向串口写入配置信息
                serialPort.BaudRate = BaudRate;
                serialPort.DataBits = DataBit;
                try                                //尝试打开串口
                {
                    serialPort.Open();
                    btnOpenSerialPort.Text = "关闭串口";
                    cmbSerialPort.Enabled = false; //控件停止交互
                    cmbBaudRate.Enabled = false;
                    cmbDataBit.Enabled = false;
                    cmbCheckBit.Enabled = false;
                    cmbStopBit.Enabled = false;
                    cmbStreamCtrl.Enabled = false;
                }
                catch                              //如果打开串口失败
                {
                    MessageBox.Show("串口打开失败\n请检查串口使用情况", "打开失败", MessageBoxButtons.OK);
                }
            }
            else     //如果串口处于打开状态
            {
                try                                //尝试关闭串口
                {
                    serialPort.Close();
                    btnOpenSerialPort.Text = "打开串口";
                    cmbSerialPort.Enabled = true; //控件开放交互
                    cmbBaudRate.Enabled = true;
                    cmbDataBit.Enabled = true;
                    cmbCheckBit.Enabled = true;
                    cmbStopBit.Enabled = true;
                    cmbStreamCtrl.Enabled = true;
                }
                catch                              //如果打开串口失败
                {
                    MessageBox.Show("串口关闭失败\n请断开所有端口", "关闭失败", MessageBoxButtons.OK);
                }
            }
        }
       /*--------------------------------------------------------
                           STOP/RUN按钮
       --------------------------------------------------------*/
        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C101a00000000b)");          //下位机接收到字符1就停止更新
                    if (string.Compare("STOP", btnStopRun.Text) == 0)  //反转标题
                        btnStopRun.Text = "RUN";
                    else
                        btnStopRun.Text = "STOP";
                }
                catch
                {
                    MessageBox.Show("发送失败\n连接断开", "发送失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
       /*--------------------------------------------------------
                           回显波形按钮
       --------------------------------------------------------*/
        private void button2_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C102a00000000b)");          //下位机接收到字符2就回显波形
                }
                catch
                {
                    MessageBox.Show("回显失败\n连接断开", "回显失败", MessageBoxButtons.OK);
                }                             
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        /*--------------------------------------------------------
                           保存波形按钮
       --------------------------------------------------------*/
        private void button3_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C103a00000000b)");          //下位机接收到字符2就回显波形
                }
                catch
                {
                    MessageBox.Show("回显失败\n连接断开", "回显失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
       /*--------------------------------------------------------
                        接收并处理下位机发来的数据
       --------------------------------------------------------*/
        public delegate void RevData(string dataRe);  //创建委托
        public delegate void RevPram(byte[] buffer);

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e) //串口接收事件
        {
            string dataRe;
            string pramRe;
            byte[] byteRead = new byte[serialPort.BytesToRead];  //BytesToRead获取接收缓冲区中数据的字节数。
            RevData receivedata = new RevData(UpdateTextbox);    //实例化委托
            RevPram receivepram = new RevPram(UpdateWavePram);
            serialPort.Read(byteRead,0,byteRead.Length);         //串口缓冲区存入数组中
            pramRe = System.Text.Encoding.Default.GetString(byteRead);
            txtFeq.Invoke(receivepram,byteRead);

            if (this.radioHexDisplay.Checked)                    //HEX显示  
            {
                for (int i = 0; i < byteRead.Length; i++)
                {
                    byte temp = byteRead[i];
                    dataRe = temp.ToString("X") + " ";
                    txbRevData.Invoke(receivedata, dataRe);
                }
            }

            if (this.radioCharDisplay.Checked)                   //字符串显示
            {
                dataRe = System.Text.Encoding.Default.GetString(byteRead);
                txbRevData.Invoke(receivedata, dataRe);
            }         
        }
       /*--------------------------------------------------------
                          更新波形各种参数
       --------------------------------------------------------*/
        private void UpdateWavePram(byte[] buffer)              //显示参数
        {
            //int length = buffer.Length;
            string str = System.Text.Encoding.Default.GetString(buffer);
            string[] split = str.Split(new Char[] { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' });

            int len = split.GetLength(0);
            if (len >= 10)   //把分割出来的数据分别放入不同地方
            {
                txtFeq.Text       = split[0];
                txtPriod.Text     = split[1];
                txtHighWidth.Text = split[2];
                txtLowWidth.Text  = split[3];
                txtDutyCycle.Text = split[4];
                txtVmax.Text      = split[5];
                txtVmin.Text      = split[6];
                txtVpp.Text       = split[7];
                txtVrms.Text      = split[8];
                txtPower.Text     = split[9];
            }
        }
       /*--------------------------------------------------------
                          更新串口发来的数据
       --------------------------------------------------------*/
        private void UpdateTextbox(string dataRe)               //显示串口
        {
            if (this.txbRevData.Text.Length > 250)              //刷新窗口
                this.txbRevData.Text = "";
            this.txbRevData.Text += dataRe;
        }
       /*--------------------------------------------------------
                           工具栏->文件->关闭程序
       --------------------------------------------------------*/
        private void 打开串口ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult temp;
            temp = MessageBox.Show("  真的要关闭示波器控制端吗?", "确认",MessageBoxButtons.YesNo,MessageBoxIcon.Warning);
            if(temp == DialogResult.Yes )
                Application.Exit();
        }
       /*--------------------------------------------------------
                           工具栏->帮助->版权信息
       --------------------------------------------------------*/
        private void 版权信息ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("     STM32数字低频示波器控制端 V1.1\n            吴思远编写 2014年1月16日\n   \t版权所有,违者必究","   版权信息");
        }
       /*--------------------------------------------------------
                           清除显示按钮
       --------------------------------------------------------*/
        private void btnClearRevData_Click(object sender, EventArgs e)
        {
            this.txbRevData.Text = "";
        }
       /*--------------------------------------------------------
                           工具栏->控制->STOP/RUN
       --------------------------------------------------------*/
        private void sTOPToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("1");          //下位机接收到字符1就停止更新
                    if (string.Compare("STOP", btnStopRun.Text) == 0)  //反转标题
                        btnStopRun.Text = "RUN";
                    else
                        btnStopRun.Text = "STOP";
                }
                catch
                {
                    MessageBox.Show("发送失败\n连接断开", "发送失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        #endregion        
        #region 增益类按钮
        //增益加
        private void button9_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C112a00000000b)");          //下位机接收到字符5                    
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //增益减
        private void button8_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C113a00000000b)");          //下位机接收到字符6                    
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
        //自动增益按下
        private void btnAutoGain_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C114a00000000b)");          //下位机接收到字符6                    
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //设置增益按下
        private void btnSetGain_Click(object sender, EventArgs e)
        {
            int length;
            string DataStream = "(C111a";  //命令头
            string temp = "3";
           
            switch (this.comboBox1.Text)
            {
                case "X0.05": temp = "1";   //和oscilloscope.h增益相对应
                    break;
                case "X0.1": temp = "2";
                    break;
                case "X1": temp = "3";
                    break;
                case "X2": temp = "4";
                    break;
                case "X4": temp = "5";
                    break;
                case "X5": temp = "6";
                    break;
                case "X10": temp = "7";
                    break;
                case "X25": temp = "8";
                    break;
                default: break;
            }
            
            if (serialPort.IsOpen)
            {
                length = 8 - temp.Length;  //数据帧长度为8,所以需要补充的0为8-len
                for (int i = 0; i < length; i++)
                {
                    DataStream += '0';
                }
                DataStream += temp; 
                DataStream += 'b';
                DataStream += ')';
                try
                {
                    serialPort.Write(DataStream);                    
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        #endregion
        #region 时基类按钮
        //设置时基按下
        private void btnSetTimeBase_Click(object sender, EventArgs e)
        {
            int length;
            string DataStream = "(C121a";
            if (serialPort.IsOpen)
            {
                length = 8 - this.comboBox2.Text.Length;  //数据帧长度为8,需要补充的0为8-len
                for (int i = 0; i < length; i++)
                {
                    DataStream += '0';
                }
                DataStream += this.comboBox2.Text;
                DataStream += 'b';
                DataStream += ')';
                try
                {
                    serialPort.Write(DataStream);                        
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //时基加按下
        private void button6_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                progressBar1.PerformStep();
                try
                {
                    serialPort.Write("(C122a00000000b)");          //下位机接收到字符3
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //时基减按下
        private void button7_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                progressBar1.PerformStep();
                try
                {
                    serialPort.Write("(C123a00000000b)");                              
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //自动时基按下
        private void btnAutoTimeBase_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                progressBar1.PerformStep();
                try
                {
                    serialPort.Write("(C124a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        #endregion       
        #region 波形发生器类按钮
        //三角波按下
        private void btnTriangleWave_Click(object sender, EventArgs e)
        {
            string DataStream_Feq = "(D1301a";
            string DataStream_Amp = "(D1302a";
            string DataStream_DutyCycle = "(D1303a";
            string sTemp;
            int len;
            float fTemp;

            this.txtCurWave.Text = "三角波";
            this.txtCurWave.Enabled = false;
            //编码频率
            len = 7 - this.txtFGFeq.Text.Length;
            for (int i = 0; i < len; i++)
                DataStream_Feq += '0';
            DataStream_Feq += this.txtFGFeq.Text;
            DataStream_Feq += "b)";
            //编码幅值
            fTemp = float.Parse(this.txtFGVpp.Text);
            fTemp = fTemp * 10;  //上位机把浮点数×10,下位机要÷回来
            sTemp = fTemp.ToString();
            len = 7 - sTemp.Length;
            for (int i = 0; i < len; i++)
                DataStream_Amp += '0';
            DataStream_Amp += sTemp;
            DataStream_Amp += "b)";
            //编码占空比
            len = 7 - this.txtFGDuty.Text.Length;
            for (int i = 0; i < len; i++)
                DataStream_DutyCycle += '0';
            DataStream_DutyCycle += this.txtFGDuty.Text;
            DataStream_DutyCycle += "b)";
            
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write(DataStream_Feq);
                    System.Threading.Thread.Sleep(2); //延时2ms给MCU足够时间处理数据
                    serialPort.Write(DataStream_Amp);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write(DataStream_DutyCycle);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write("(C131a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //矩形波按下
        private void btnRectangularWave_Click(object sender, EventArgs e)
        {
            string DataStream_Feq = "(D1301a";
            string DataStream_Amp = "(D1302a";
            string DataStream_DutyCycle = "(D1303a";
            string sTemp;
            int len;
            float fTemp;

            this.txtCurWave.Text = "矩形波";
            this.txtCurWave.Enabled = false;
            //编码频率
            len = 7 - this.txtFGFeq.Text.Length;
            for (int i = 0; i < len; i++)
                DataStream_Feq += '0';
            DataStream_Feq += this.txtFGFeq.Text;
            DataStream_Feq += "b)";
            //编码幅值
            fTemp = float.Parse(this.txtFGVpp.Text);
            fTemp = fTemp * 10;  //上位机把浮点数×10,下位机要÷回来
            sTemp = fTemp.ToString();
            len = 7 - sTemp.Length;
            for (int i = 0; i < len; i++)
                DataStream_Amp += '0';
            DataStream_Amp += sTemp;
            DataStream_Amp += "b)";
            //编码占空比
            len = 7 - this.txtFGDuty.Text.Length;
            for (int i = 0; i < len; i++)
                DataStream_DutyCycle += '0';
            DataStream_DutyCycle += this.txtFGDuty.Text;
            DataStream_DutyCycle += "b)";

            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write(DataStream_Feq);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write(DataStream_Amp);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write(DataStream_DutyCycle);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write("(C132a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //正弦波按下
        private void btnSineWave_Click(object sender, EventArgs e)
        {
            string DataStream_Feq = "(D1301a";
            string DataStream_Amp = "(D1302a";
            string DataStream_DutyCycle = "(D1303a";
            string sTemp;
            int len;
            float fTemp;

            this.txtCurWave.Text = "正弦波";
            this.txtCurWave.Enabled = false;
            //编码频率
            len = 7 - this.txtFGFeq.Text.Length;
            for (int i = 0; i < len; i++)
                DataStream_Feq += '0';
            DataStream_Feq += this.txtFGFeq.Text;
            DataStream_Feq += "b)";
            //编码幅值
            fTemp = float.Parse(this.txtFGVpp.Text);
            fTemp = fTemp * 10;  //上位机把浮点数×10,下位机要÷回来
            sTemp = fTemp.ToString();
            len = 7 - sTemp.Length;
            for (int i = 0; i < len; i++)
                DataStream_Amp += '0';
            DataStream_Amp += sTemp;
            DataStream_Amp += "b)";
            //编码占空比
            len = 7 - this.txtFGDuty.Text.Length;
            for (int i = 0; i < len; i++)
                DataStream_DutyCycle += '0';
            DataStream_DutyCycle += this.txtFGDuty.Text;
            DataStream_DutyCycle += "b)";

            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write(DataStream_Feq);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write(DataStream_Amp);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write(DataStream_DutyCycle);
                    System.Threading.Thread.Sleep(2);
                    serialPort.Write("(C133a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //白噪声按下
        private void btnNoiseWave_Click(object sender, EventArgs e)
        {
            this.txtCurWave.Text = "白噪声";
            this.txtCurWave.Enabled = false;

            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C134a00004096b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //扫频按下
        private void btnSwapFeq_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C135a00000000b)");
                    if(String.Compare(this.btnSwapFeq .Text,"开始扫频") == 0) 
                        this.btnSwapFeq.Text = "停止扫频";
                    if (String.Compare(this.btnSwapFeq.Text,"停止扫频") == 0)
                        this.btnSwapFeq.Text = "开始扫频";
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        #endregion        
        #region 信号分析类按钮
        //傅立叶分析按下
        private void button10_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C141a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //频谱分析
        private void button11_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C142a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //功率谱分析
        private void button12_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C143a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //交流分析按下
        private void button13_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C144a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //直流分析按下
        private void button14_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C145a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        #endregion       
        #region AC/DC耦合
        //交流耦合按下
        private void button1_Click_1(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C104a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        //直流耦合按下
        private void button4_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                try
                {
                    serialPort.Write("(C105a00000000b)");
                }
                catch
                {
                    MessageBox.Show("失败\n连接断开", "失败", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("发送失败\n串口已关闭", "发送失败", MessageBoxButtons.OK);
            }
        }
        #endregion

    }
}