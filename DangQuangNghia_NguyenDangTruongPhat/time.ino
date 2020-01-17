
/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int BCDtoDEC(byte num)
{
  return((num / 16) * 10 + (num % 16)); 
}
/* Chuyển từ Decimal sang BCD */
int DECtoBCD(byte num)
{
  return((num / 10) * 16 + (num % 10)); 
}


void setTime(byte gio, byte phut, byte giay, byte thu, byte ngay, byte thang, byte nam)
{
  Wire.beginTransmission(0x68);/* bắt đầu giao tiếp với DS1307 0x68 ở đây là địa chỉ của DS1307 */
  Wire.write(byte(0x00));
  Wire.write(DECtoBCD(giay));
  Wire.write(DECtoBCD(phut));
  Wire.write(DECtoBCD(gio));
  Wire.write(DECtoBCD(thu)); 
  Wire.write(DECtoBCD(ngay)); 
  Wire.write(DECtoBCD(thang));
  Wire.write(DECtoBCD(nam));
  Wire.endTransmission(); /* kết thúc giao tiếp */ 
}


void getTime()
{
  Wire.beginTransmission(0x68);/*mặc định ta bắt đầu với địa chủ của DS1307*/
  Wire.write(byte(0x00));/*trả về byte bắt đầu thứ 0*/
  Wire.endTransmission();
  Wire.requestFrom(0x68, 7); /* yêu cầu ds1307 nhả ra 7 byte dữ liệu */
  giay = BCDtoDEC(Wire.read());/* bắt đầu đọc dữ liệu ra ngoài */
  phut = BCDtoDEC(Wire.read());
  gio = BCDtoDEC(Wire.read());
  thu = BCDtoDEC(Wire.read());
  ngay = BCDtoDEC(Wire.read());
  thang = BCDtoDEC(Wire.read());
  nam = BCDtoDEC(Wire.read());
  nam = nam + 2000; /* ở đây vì DS1307 trả về hai số cuối của năm
  cần phải cộng thêm 2000 */
}
