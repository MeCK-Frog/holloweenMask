// LovyanGFX SPIバスおよび使用パネルの設定を伴う使い方
// https://github.com/lovyan03/LovyanGFX/tree/master/examples/HowToUse/2_spi_settingからソースを使用しています。

// ヘッダをincludeします。
#include <LovyanGFX.hpp>

//NodeMCU and ST7789 Pinout(ESP8266)
//https://simple-circuit.com/esp8266-nodemcu-st7789-tft-ips-display/
//GND = GND
//VCC = VCC
//SCL = D5 = HSCLK
//SDA = D7 = HMOSI
//RES = D2 = GPIO4
//DC = D1 = GPIO5
//BLK = VCC

//ESP32 DEVKIT V1
//VSPI MOSI = GPIO23 = SDA
//VSPI MISO = GPIO19(使わないかも) =?
//VSPI CLK = GPIO18 = SCL
//DC  = GPIO17 = DC
//RST = GPIO16 = RES

// SPI設定用の構造体を用意します。
// 構造体の名称に決まりはありませんが、
// 構造体の各メンバ変数の名前と型は例の通りにしてください。
struct LGFX_Config {

  // 使用するSPIを VSPI_HOST または HSPI_HOST で設定します。
  static constexpr spi_host_device_t spi_host = VSPI_HOST;

  // 使用するDMAチャンネルを 1か2で設定します。
  // 使用しない場合は省略するか0を設定します。
  static constexpr int dma_channel = 1;

  // SPIのSCLKのピン番号を設定します。
  static constexpr int spi_sclk = 18;

  // SPIのMOSIのピン番号を設定します。
  static constexpr int spi_mosi = 23;

  // SPIのMISOのピン番号を設定します。
  // SDカード等と共通のSPIバスを使う場合はMISOも必ず設定してください。
  // 使わない場合は省略するか-1を設定します。
  static constexpr int spi_miso = -1;

  // SPI通信のデータ長を指定します。
  // RaspberryPi用のLCD等を使用する場合に16を指定します。
  // 省略時は 8 です。大抵のパネルは8ですので、基本的には省略してください。
//static constexpr int spi_dlen = 16;
};

// 用意した設定用の構造体を、LGFX_SPIクラスにテンプレート引数として設定し、インスタンスを作成します。
static lgfx::LGFX_SPI<LGFX_Config> lcd1;
static lgfx::LGFX_SPI<LGFX_Config> lcd2;
static lgfx::LGFX_SPI<LGFX_Config> lcd3;


// Panelクラスのインスタンスを作成します。使用するパネルにあったクラスを選択してください。
//パネルをST7789に設定
//static lgfx::Panel_DDUINO32_XS panel;
//static lgfx::Panel_LoLinD32 panel;
//static lgfx::Panel_M5Stack panel;
//static lgfx::Panel_M5StickC panel;
//static lgfx::Panel_ODROID_GO panel;
//static lgfx::Panel_TTGO_TS panel;
//static lgfx::Panel_TTGO_TWatch panel;

//static lgfx::Panel_HX8357B panel;
//static lgfx::Panel_HX8357D panel;
//static lgfx::Panel_ILI9163 panel;
//static lgfx::Panel_ILI9341 panel;
//static lgfx::Panel_ILI9342 panel;
//static lgfx::Panel_ILI9486 panel;
//static lgfx::Panel_ILI9488 panel;
//static lgfx::Panel_SSD1351 panel;
static lgfx::Panel_ST7789 panel1;
static lgfx::Panel_ST7789 panel2;
//static lgfx::Panel_ST7735S panel;



void setup(void)
{
 Serial.begin(115200);
// パネルクラスに各種設定値を代入していきます。
// （LCD一体型製品のパネルクラスを選択した場合は、
//   製品に合った初期値が設定されているので設定は不要です）

  // 通常動作時のSPIクロックを設定します。
  // ESP32のSPIは80MHzを整数で割った値のみ使用可能です。
  // 設定した値に一番近い設定可能な値が使用されます。
  panel1.freq_write = 20000000;
  panel2.freq_write = 20000000;

  // 単色の塗り潰し処理時のSPIクロックを設定します。
  // 基本的にはfreq_writeと同じ値を設定しますが、
  // より高い値を設定しても動作する場合があります。
  panel1.freq_fill  = 20000000;
  panel2.freq_fill  = 20000000;

  // LCDから画素データを読取る際のSPIクロックを設定します。
  panel1.freq_read  = 20000000;
  panel2.freq_read  = 20000000;

  // SPI通信モードを0~3から設定します。
  panel1.spi_mode = 3;
  panel2.spi_mode = 3;

  // データ読み取り時のSPI通信モードを0~3から設定します。
  panel1.spi_mode_read = 0;
  panel2.spi_mode_read = 0;

  // 画素読出し時のダミービット数を設定します。
  // 画素読出しでビットずれが起きる場合に調整してください。
  panel1.len_dummy_read_pixel = 8;
  panel2.len_dummy_read_pixel = 8;

  // データの読取りが可能なパネルの場合はtrueを、不可の場合はfalseを設定します。
  // 省略時はtrueになります。
  panel1.spi_read = false;
  panel2.spi_read = false;
  
  // データの読取りMOSIピンで行うパネルの場合はtrueを設定します。
  // 省略時はfalseになります。
  panel1.spi_3wire = false;
  panel2.spi_3wire = false;

  // LCDのCSを接続したピン番号を設定します。
  // 使わない場合は省略するか-1を設定します。
  // CSはST7789に存在しないため省略
  panel1.spi_cs = -1;
  panel2.spi_cs = -1;

  // LCDのDCを接続したピン番号を設定します省略。
  // 変更
  panel1.spi_dc = 17;
  panel2.spi_dc = 4;
  
  // LCDのRSTを接続したピン番号を設定します。
  // 使わない場合は省略するか-1を設定します。
  // 変更
  panel1.gpio_rst = 16;
  panel2.gpio_rst = -1;

  // LCDのバックライトを接続したピン番号を設定します。
  // 使わない場合は省略するか-1を設定します。
  // 変更
  panel1.gpio_bl  = -1;
  panel2.gpio_bl  = -1;

  // バックライト使用時、輝度制御に使用するPWMチャンネル番号を設定します。
  // PWM輝度制御を使わない場合は省略するか-1を設定します。
  // 変更
  panel1.pwm_ch_bl = -1;
  panel2.pwm_ch_bl = -1;
  
  // バックライト点灯時の出力レベルがローかハイかを設定します。
  // 省略時は true。true=HIGHで点灯 / false=LOWで点灯になります。
  panel1.backlight_level = true;
  panel2.backlight_level = true;


  // invertDisplayの初期値を設定します。trueを設定すると反転します。
  // 省略時は false。画面の色が反転している場合は設定を変更してください。
  panel1.invert = true;
  panel2.invert = true;
  // パネルの色順がを設定します。  RGB=true / BGR=false
  // 省略時はfalse。赤と青が入れ替わっている場合は設定を変更してください。
  panel1.rgb_order = true;
  panel2.rgb_order = true;
  // パネルのメモリが持っているピクセル数（幅と高さ）を設定します。
  // 設定が合っていない場合、setRotationを使用した際の座標がずれます。
  // （例：ST7735は 132x162 / 128x160 / 132x132 の３通りが存在します）
  panel1.memory_width  = 240;
  panel1.memory_height = 320;
  panel2.memory_width  = 240;
  panel2.memory_height = 320;
  // パネルの実際のピクセル数（幅と高さ）を設定します。
  // 省略時はパネルクラスのデフォルト値が使用されます。
  panel1.panel_width  = 240;
  panel1.panel_height = 240;
  panel2.panel_width  = 240;
  panel2.panel_height = 240;
  
  // パネルのオフセット量を設定します。
  // 省略時はパネルクラスのデフォルト値が使用されます。
  panel1.offset_x = 0;
  panel1.offset_y = 0;
  panel2.offset_x = 0;
  panel2.offset_y = 0;

  // setRotationの初期化直後の値を設定します。
  panel1.rotation = 0;
  panel2.rotation = 0;

  // setRotationを使用した時の向きを変更したい場合、offset_rotationを設定します。
  // setRotation(0)での向きを 1の時の向きにしたい場合、 1を設定します。
  panel1.offset_rotation = 0;
  panel2.offset_rotation = 0;

  // 設定を終えたら、LGFXのsetPanel関数でパネルのポインタを渡します。
  lcd1.setPanel(&panel1);
  lcd2.setPanel(&panel2);
  //lcd3.setPanel(&panel);

  // SPIバスの初期化とパネルの初期化を実行すると使用可能になります。
  lcd1.init();
  //lcd2.init();
  //lcd3.init();

  lcd1.drawRect(0,0,lcd1.width(),lcd1.height(),0xFFFF);
  lcd2.drawRect(0,0,lcd1.width(),lcd1.height(),0xFFFF);
  //lcd3.drawRect(0,0,lcd1.width(),lcd1.height(),0xFFFF);

  lcd1.setTextSize(2);
  lcd2.setTextSize(2);
  //lcd3.setTextSize(2);
}

uint32_t count = ~0;
void loop(void)
{
  lcd1.startWrite();
  lcd1.setRotation(++count & 7);
  lcd1.setTextColor(random(65536));
  lcd1.drawNumber(lcd1.getRotation(), 16, 0);
  lcd1.setTextColor(0xFF0000U);
  lcd1.drawString("R", 30, 16);
  lcd1.setTextColor(0x00FF00U);
  lcd1.drawString("G", 40, 16);
  lcd1.setTextColor(0x0000FFU);
  lcd1.drawString("B", 50, 16);
  lcd1.drawRect(30,30,lcd1.width()-60,lcd1.height()-60,random(65536));
  lcd1.endWrite();

  lcd2.startWrite();
  lcd2.setRotation(++count & 7);
  lcd2.setTextColor(random(65536));
  lcd2.drawNumber(lcd1.getRotation(), 16, 0);
  lcd2.setTextColor(0xFF0000U);
  lcd2.drawString("R", 30, 16);
  lcd2.setTextColor(0x00FF00U);
  lcd2.drawString("G", 40, 16);
  lcd2.setTextColor(0x0000FFU);
  lcd2.drawString("B", 50, 16);
  lcd2.drawRect(30,30,lcd1.width()-60,lcd1.height()-60,random(65536));
  lcd2.endWrite();
}
