using System;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Gamepadtest;
using System.IO.Ports;


namespace BigPapaDs
{
    public partial class iRoboticsCommandCenter : Form
    {
        const int baudrate = 57600;                     // xbee serial port baudrate (bits per second)
        const int delay = 10;                           // delay for updating the controller values and sending the packet (milliseconds)

        GamepadState controller;
        System.Windows.Threading.DispatcherTimer controllerUpdateTimer;
        private StringBuilder recievedData1 = new StringBuilder();
        private StringBuilder recievedDataMain = new StringBuilder();
        private byte[] buttonstate = new byte[10];

        public iRoboticsCommandCenter()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            foreach (string portname in SerialPort.GetPortNames())
            {
                dropDownComboBox1.Items.Add(portname);
                controllerComboBox.Items.Add(portname);

            }
            timer1.Start();
        }

        private void connectButton_Click(object sender, EventArgs e)
        {
            if (connectButton.Text == "Connect")
            {
                controller = new GamepadState(SlimDX.XInput.UserIndex.One);
                if (controller.Connected)
                {
                    connectedTextBox.Text = "Connected";
                }
                else
                {
                    connectedTextBox.Text = "Disconnected";
                }
            }
            if (controllerUpdateTimer == null)
            {
                controllerUpdateTimer = new System.Windows.Threading.DispatcherTimer();
                controllerUpdateTimer.Interval = new TimeSpan(0, 0, 0, 0, delay); 
                controllerUpdateTimer.Tick += new EventHandler(updateControllerState);
                controllerUpdateTimer.Start();
            }

        }

        private void updateControllerState(object o, EventArgs e)
        {
            if (controller != null)
            {
                controller.Update();

                leftStickXTextBox.Text = " " + Convert.ToByte(controller.LeftStick.Position.X * 100 + 100).ToString();
                leftStickYTextBox.Text = " " + Convert.ToByte(controller.LeftStick.Position.Y * 100 + 100).ToString();

                rightStickXTextBox.Text = " " + Convert.ToByte(controller.RightStick.Position.X * 100 + 100).ToString();
                rightStickYTextBox.Text = " " + Convert.ToByte(controller.RightStick.Position.Y * 100 + 100).ToString();

                rightBumperTextBox.Text = " " + controller.RightShoulder.ToString();
                leftBumperTextBox.Text = " " + controller.LeftShoulder.ToString();

                leftTriggerTextBox.Text = " " + Convert.ToByte(controller.LeftTrigger * 100).ToString();
                rightTriggerTextBox.Text = " " + Convert.ToByte(controller.RightTrigger * 100).ToString();

                upDpadTextBox.Text = " " + controller.DPad.Up.ToString();
                downDpadTextBox.Text = " " + controller.DPad.Down.ToString();
                rightDpadTextBox.Text = " " + controller.DPad.Right.ToString();
                leftDpadTextBox.Text = " " + controller.DPad.Left.ToString();

                backTextBox.Text = " " + controller.Back.ToString();
                startButtonTextBox.Text = " " + controller.Start.ToString();

                textBox1.Text = " " + controller.LeftStick.Clicked.ToString();
                textBox2.Text = " " + controller.RightStick.Clicked.ToString();

                aButtonTextBox.Text = " " + controller.A.ToString();
                bButtonTextBox.Text = " " + controller.B.ToString();
                xButtonTextBox.Text = " " + controller.X.ToString();
                yButtonTextBox.Text = " " + controller.Y.ToString();

            }

            Task updatecontrollerStateTask = new Task(() => updateControllerBuffers());
            updatecontrollerStateTask.Start();

        }

        private void updateControllerBuffers()
        {
            if (controller != null)
            {

                //        | byte 0        | byte 1        | byte 2        | byte 3        | byte 4        | byte 5        | byte 6        | byte 7        | byte 8        | byte9       |
                //
                //  LSB     255             start           back            left stick X    left stick Y    right stick X   right stick Y   left trigger    right trigger   254
                //   |          "   "       right bumper    right click         "   "           "   "           "   "           "   "           "   "           "   "           "   "       
                //   |          "   "       left bumper     left click          "   "           "   "           "   "           "   "           "   "           "   "           "   "       
                //   |          "   "       Y               dpad right          "   "           "   "           "   "           "   "           "   "           "   "           "   "       
                //   |          "   "       X               dpad left           "   "           "   "           "   "           "   "           "   "           "   "           "   "       
                //   |          "   "       B               dpad down           "   "           "   "           "   "           "   "           "   "           "   "           "   "       
                //   |          "   "       A               dpad up             "   "           "   "           "   "           "   "           "   "           "   "           "   "       
                //  MSB         "   "       0(unused)       0(unused)           "   "           "   "           "   "           "   "           "   "           "   "           "   "       

                int x = 0;

                buttonstate[0] = Convert.ToByte(255);

                x = (Convert.ToInt32(controller.A) << 6) |
                    (Convert.ToInt32(controller.B) << 5) |
                    (Convert.ToInt32(controller.X) << 4) |
                    (Convert.ToInt32(controller.Y) << 3) |
                    (Convert.ToInt32(controller.LeftShoulder) << 2) |
                    (Convert.ToInt32(controller.RightShoulder) << 1) |
                    Convert.ToInt32(controller.Start);

                buttonstate[1] = Convert.ToByte(x);

                x = (Convert.ToInt32(controller.DPad.Up) << 6) |
                    (Convert.ToInt32(controller.DPad.Down) << 5) |
                    (Convert.ToInt32(controller.DPad.Left) << 4) |
                    (Convert.ToInt32(controller.DPad.Right) << 3) |
                    (Convert.ToInt32(controller.LeftStick.Clicked) << 2) |
                    (Convert.ToInt32(controller.RightStick.Clicked) << 1) |
                    Convert.ToInt32(controller.Back);

                buttonstate[2] = Convert.ToByte(x);

                buttonstate[3] = Convert.ToByte(controller.LeftStick.Position.X * 100 + 100);

                buttonstate[4] = Convert.ToByte(controller.LeftStick.Position.Y * 100 + 100);

                buttonstate[5] = Convert.ToByte(controller.RightStick.Position.X * 100 + 100);

                buttonstate[6] = Convert.ToByte(controller.RightStick.Position.Y * 100 + 100);

                buttonstate[7] = Convert.ToByte(controller.LeftTrigger * 100);

                buttonstate[8] = Convert.ToByte(controller.RightTrigger * 100);

                buttonstate[9] = Convert.ToByte(254);
            }
        }

        private void openButton1_Click(object sender, EventArgs e)
        {
            if (dropDownComboBox1.Text == "")
            {
                return;
            }
            if (!serialPort1.IsOpen)
            {
                if (serialPort3.PortName == dropDownComboBox1.Text && (serialPort3.IsOpen))
                {
                    dropDownComboBox1.Text = "";
                    return;
                }
                serialPort1.PortName = dropDownComboBox1.Text;
                serialPort1.Open();
            }
        }

        private void closeButton1_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                dropDownComboBox1.Text = "";
            }
        }

        private void iRoboticsCommandCenter_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
            
        }

        private void sendXbeeButton1_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Write(sendMessageTextBox1.Text + "\n\r");
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            recievedData1.Append(serialPort1.ReadExisting());
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            consoleTextBox1.Text = recievedData1.ToString();
            
            dataRecievedTextBox.Text = recievedDataMain.ToString();

        }

        private void controllerOpenButton_Click(object sender, EventArgs e)
        {
            if (controllerComboBox.Text == "")
            {
                return;
            }

            if (!serialPort3.IsOpen)
            {
                if (serialPort1.PortName == controllerComboBox.Text && (serialPort1.IsOpen))
                {
                    controllerComboBox.Text = "";
                    return;
                }
                serialPort3.PortName = controllerComboBox.Text;
                serialPort3.BaudRate = baudrate;
                serialPort3.Open();
            }
            Task SendControllerValuesTask = new Task(() => sendControllerValues());
            SendControllerValuesTask.Start();
        }

        private void controllerCloseButton_Click(object sender, EventArgs e)
        {
            if (serialPort3.IsOpen)
            {
                serialPort3.Close();
                controllerComboBox.Text = "";
            }
        }

        private void serialPort3_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            recievedDataMain.Append(serialPort3.ReadExisting());
        }

        private void sendControllerValues()
        {
            while (serialPort3.IsOpen)
            {
                try
                {
                    serialPort3.Write(buttonstate, 0, 10);
                    System.Threading.Thread.Sleep(delay);
                    serialPort3.DiscardOutBuffer();
                }
                catch
                {
                    return;
                }
            }
        }

        private void refreshPortsButton_Click(object sender, EventArgs e)
        {

            if (serialPort3.IsOpen)
            {
                serialPort3.Close();
            }

            if (controllerComboBox.Text == "")
            {
                return;
            }

            if (!serialPort3.IsOpen)
            {
                serialPort3.PortName = controllerComboBox.Text;
                serialPort3.BaudRate = baudrate;
                serialPort3.Open();
            }
            Task SendControllerValuesTask = new Task(() => sendControllerValues());
            SendControllerValuesTask.Start();
        }

        private void dataRecievedTextBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}