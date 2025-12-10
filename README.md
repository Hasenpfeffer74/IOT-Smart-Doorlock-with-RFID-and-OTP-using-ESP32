# IOT Smart Doorlock with RFID & OTP using ESP32
> **Lưu ý:** Đây là dự án đại học đầu tiên của chúng em, sẽ có nhiều sai sót. Rất mong nhận được sự thông cảm và góp ý của mọi người.
## Giới thiệu (VN)
Dự án cung cấp một hệ thống khóa cửa thông minh sử dụng ESP32 với ba phương thức mở khóa: thẻ RFID, mã OTP và mã PIN. Hệ thống được thiết kế đơn giản, dễ tích hợp và phù hợp cho các ứng dụng nhà trọ, văn phòng hoặc mô hình IoT học thuật.

Hệ thống gồm các thành phần chính: ESP32, RC522 RFID, Keypad 4x4, LCD I2C, relay điều khiển khóa từ, buzzer và nguồn DC–DC. ESP32 kết nối Wi-Fi để gửi OTP qua Internet.

## Tính năng
* Mở khóa bằng thẻ RFID đã đăng ký.
* Mở khóa bằng OTP được gửi qua Telegram/email/app.
* Mở khóa bằng mã PIN cố định.
* Hiển thị trạng thái trên LCD.
* Ghi log lượt mở khóa.
* Điều khiển khóa bằng relay hoặc servo.

## Phần cứng chính
* **Vi điều khiển:** ESP32 Devkit.
* **Đầu đọc thẻ:** RFID RC522.
* **Nhập liệu:** Keypad 4×4.
* **Hiển thị:** LCD 1602 I2C.
* **Cơ cấu chấp hành:** Relay 5V điều khiển khóa điện từ 12V.
* **Thông báo:** Buzzer + LED báo trạng thái.
* **Nguồn:** Ổn áp nguồn từ 12V → 5V → 3.3V.

## Cách hoạt động
1.  Người dùng chọn phương thức: RFID, OTP hoặc PIN.
2.  ESP32 xử lý thông tin, kiểm tra tính hợp lệ.
3.  Nếu xác thực thành công, relay cấp nguồn cho khóa điện từ → cửa mở.
4.  Hệ thống tự động khóa lại sau vài giây.

---

# English Version
> **Note:** This is our first university project, so there may be errors and shortcomings. We highly appreciate your understanding and feedback.
## Introduction
This project implements a simple IoT smart doorlock system using an ESP32. It supports three authentication methods: RFID card, OTP code, and PIN input. The system is designed to be lightweight, easy to integrate, and suitable for home, office, or academic IoT demonstration projects.

It uses common hardware modules such as ESP32, RC522, keypad, LCD display, and a relay to drive a 12V solenoid lock.

## Features
* Unlock with registered RFID card.
* Unlock with OTP sent via Telegram/email/app.
* Unlock with a predefined PIN code.
* LCD display for status messages.
* Event logging for all unlock attempts.
* Relay/servo to control the lock mechanism.

## Hardware Overview
* **Controller:** ESP32 Devkit board.
* **Reader:** RC522 RFID reader.
* **Input:** 4×4 keypad.
* **Display:** LCD 1602 I2C.
* **Actuator:** 5V relay controlling 12V solenoid lock.
* **Notification:** Buzzer and indicator LED.
* **Power:** 12V → 5V/3.3V power modules.

## How It Works
1.  User chooses RFID, OTP, or PIN authentication.
2.  ESP32 verifies the credentials.
3.  If valid, relay activates and unlocks the door.
4.  The system automatically locks again after a short delay.
