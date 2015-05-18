/******************** (C) COPYRIGHT 2013 BUILDWIN ********************************
* File Name          : gpdma.c
* Author             : tingliu
* Version            : V1018a
* Date               : 10/18/2013
* Description        : This file provides all the main flow of the menu functions.
**********************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

char const some_chars[] = "-:/!,._1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";		//for font build tools to set this chars into font.bin

char const simplified_chinese[] = "简体中文";
char const traditional_chinese[] = "繁體中文";
char const english[] = "English";
char const russian[] = "Русско";
char const korean[] = "한국어";
char const japanese[]= "日本語";
char const spanish[] = "Español";
char const turkey[] = "türkiye";
char const hebrew[] = "עברית";
char const thai[] = "ไทย";
char const polish[] = "polski";

char const off_cns[] = "关";
char const off_cnt[] = "關";
char const off_en[] = "Off";
char const off_ru[] = "Выкл.";
char const off_ko[] = "오프";
char const off_ja[] = "オフ";
char const off_spa[] = "Activado";  
char const off_tu[] = "Kapali";  
char const off_he[] = "כבוי";  
char const off_th[] = "ปิด";  
char const off_po[] = "wyłączać";  

char const on_cns[] = "开";
char const on_cnt[] = "開";
char const on_en[] = "On";
char const on_ru[] = "Вкл.";
char const on_ko[] = "온";
char const on_ja[] = "オン";
char const on_spa[] = "Desactivado";
char const on_tu[] = "Açik";
char const on_he[] = "דלוק";
char const on_th[] = "เปิด";
char const on_po[] = "Otwarte";

char const one_minute_cns[] = "1分钟";
char const one_minute_cnt[] = "1分鐘";
char const one_minute_en[] = "One Minute";
char const one_minute_ru[] = "1 мн.";
char const one_minute_ko[] = "1분";
char const one_minute_ja[] = "1分間";
char const one_minute_spa[] = "1 min";
char const one_minute_tu[] = "1 Dakika";
char const one_minute_he[] = "1 דקה";
char const one_minute_th[] = "1นาที";
char const one_minute_po[] = "1 minuta";

char const three_minute_cns[] = "3分钟";
char const three_minute_cnt[] = "3分鐘";
char const three_minute_en[] = "Three Minute";
char const three_minute_ru[] = "3 мн.";
char const three_minute_ko[] = "3분";
char const three_minute_ja[] = "3分間";
char const three_minute_spa[] = "3 min";
char const three_minute_tu[] = "3 Dakika";
char const three_minute_he[] = "3דקות";
char const three_minute_th[] = "3นาที";
char const three_minute_po[] = "3 minuty";

char const five_minute_cns[] = "5分钟";
char const five_minute_cnt[] = "5分鐘";
char const five_minute_en[] = "Five Minute";
char const five_minute_ru[] = "5 мн.";
char const five_minute_ko[] = "5분";
char const five_minute_ja[] = "5分間";
char const five_minute_spa[] = "5 min";
char const five_minute_tu[] = "5 Dakika";
char const five_minute_he[] = "5דקות";
char const five_minute_th[] = "5นาที";
char const five_minute_po[] = "5 minut";

char const ten_minute_cns[] = "10分钟";
char const ten_minute_cnt[] = "10分鐘";
char const ten_minute_en[] = "ten Minute";
char const ten_minute_ru[] = "10 мн.";
char const ten_minute_ko[] = "10분";
char const ten_minute_ja[] = "10分間";
char const ten_minute_spa[] = "10 min";
char const ten_minute_tu[] = "10 Dakika";
char const ten_minute_he[] = "10דקות";
char const ten_minute_th[] = "10นาที";
char const ten_minute_po[] = "10 minut";

char const fre_50hz_cns[] = "50 HZ";
char const fre_60hz_cns[] = "60 HZ";
char const cancel_cns[] = "取消";
char const cancel_cnt[] = "取消";
char const cancel_en[] = "Cancel";
char const cancel_ru[] = "Отмена";
char const cancel_ko[] = "최소";
char const cancel_ja[] = "キャンセル";
char const cancel_spa[] = "Cancelar";
char const cancel_tu[] = "Iptal";
char const cancel_he[] = "בטל";
char const cancel_th[] = "ยกเลิก";
char const cancel_po[] = "Anulować";

char const ok_cns[] = "确认";
char const ok_cnt[] = "確認";
char const ok_en[] = "OK";
char const ok_ru[] = "Подтверждение";
char const ok_ko[] = "확인";
char const ok_ja[] = "確認";
char const ok_spa[] = "Confirmar";
char const ok_tu[] = "Tamam";
char const ok_he[] = "אשר";
char const ok_th[] = "ตกลง";
char const ok_po[] = "Potwierdzać";

char const no_cns[] = "否";
char const no_cnt[] = "否";
char const no_en[] = "NO";
char const no_ru[] = "Нет";
char const no_ko[] = "아니요";
char const no_ja[] = "いいえ";
char const no_spa[] = "No";
char const no_tu[] = "Hayır";
char const no_he[] = "בטל";
char const no_th[] = "ไม่";
char const no_po[] = "Nie";

char const yes_cns[] = "是";
char const yes_cnt[] = "是";
char const yes_en[] = "YES";
char const yes_ru[] = "Да";
char const yes_ko[] = "예";
char const yes_ja[] = "はい";
char const yes_spa[] = "Si";
char const yes_tu[] = "Evet";
char const yes_he[] = "אשר";
char const yes_th[] = "ใช่";
char const yes_po[] = "Tak";

char const date_time_cns[] = "时间设定";
char const date_time_cnt[] = "時間設定";
char const date_time_en[] = "Time Setting";
char const date_time_ru[] = "Установка времени";
char const date_time_ko[] = "시간 설정";
char const date_time_ja[] = "時間設定";
char const date_time_spa[] = "Ajuste de la hora";
char const date_time_tu[] = "Zaman Seti";
char const date_time_he[] = "הזמן Set";
char const date_time_th[] = "ตั้งเวลา";
char const date_time_po[] = "Ustaw czas";

char const auto_off_cns[] = "自动关机";
char const auto_off_cnt[] = "自動關機";
char const auto_off_en[] = "Auto Power-Off";
char const auto_off_ru[] = "Авто. выкл.";
char const auto_off_ko[] = "오토 파워 오프";
char const auto_off_ja[] = "自動シャットダウン";
char const auto_off_spa[] = "Autodesactivado" ;
char const auto_off_tu[] = "Otomatik kapatma" ;
char const auto_off_he[] = "כיבוי אוטומטי" ;
char const auto_off_th[] = "ปิดอัตโนมัติ" ;
char const auto_off_po[] = "Automatyczne wyłączanie" ;

char const lanuage_setting_cns[] = "语言";
char const lanuage_setting_cnt[] = "語言";
char const lanuage_setting_en[] = "Language Setting";
char const lanuage_setting_ru[] = "Настройка языка";
char const lanuage_setting_ko[] = "언어 설정";
char const lanuage_setting_ja[] = "言語設定";
char const lanuage_setting_spa[] = "Ajustar idioma";
char const lanuage_setting_tu[] = "Dil Ayarları";
char const lanuage_setting_he[] = "בחירת שפות";
char const lanuage_setting_th[] = "ภาษา";
char const lanuage_setting_po[] = "Ustawienie języka";

char const light_freq_cns[] = "光源频率";
char const light_freq_cnt[] = "光源頻率";
char const light_freq_en[] = "Frequency";
char const light_freq_ru[] = "Частота ИСТ.";
char const light_freq_ko[] = "광원 주파수";
char const light_freq_ja[] = "光源頻度";
char const light_freq_spa[] = "Frecuencia Luz";
char const light_freq_tu[] = "Işık frekansı";
char const light_freq_he[] = "תדירות אור";
char const light_freq_th[] = "ความถี่";
char const light_freq_po[] = "Częstotliwość światła";

char const screen_protecting_cns[] = "自动关屏";
char const screen_protecting_cnt[] = "自動關屏";
char const screen_protecting_en[] = "Screen savers";
char const screen_protecting_ru[] = "Защита экрана";
char const screen_protecting_ko[] = "스크린 세이버";
char const screen_protecting_ja[] = "スクリーン保護";
char const screen_protecting_spa[] = "Proteccion pantalla";
char const screen_protecting_tu[] = "Ekran koruyucular";
char const screen_protecting_he[] = "שומרי מסך";
char const screen_protecting_th[] = "ป้อวกันเจอภาพ";
char const screen_protecting_po[] = "Wygaszacz ekranu";

char const Picture_rotating_cns[] = "图片旋转";
char const Picture_rotating_cnt[] = "圖片旋轉";
char const Picture_rotating_en[] = "Video Rotate";
char const Picture_rotating_ru[] = "Поворот изображения";
char const Picture_rotating_ko[] = "이미지 로테이터";
char const Picture_rotating_ja[] = "画像回転";
char const Picture_rotating_spa[] = "Giro imagen";
char const Picture_rotating_tu[] = "Video Döndürme";
char const Picture_rotating_he[] = "סיבוב תצוגה";
char const Picture_rotating_th[] = "แสดงภาพ";
char const Picture_rotating_po[] = "Obracanie zdjęć";

char const defaulting_cns[] = "重设系统";
char const defaulting_cnt[] = "重設系統";
char const defaulting_en[] = "Reset System";
char const defaulting_ru[] = "Переустановка системы";
char const defaulting_ko[] = "시스템 재설정";
char const defaulting_ja[] = "システムをリセット";
char const defaulting_spa[] = "Restablecimiento del sistema";
char const defaulting_tu[] = "Standart";
char const defaulting_he[] = "ברירת מחדל";
char const defaulting_th[] = "ตั้งค่า";
char const defaulting_po[] = "Ustawienie domyślne";

char const formating_cns[] = "格式化";
char const formating_cnt[] = "格式化";
char const formating_en[] = "Format";
char const formating_ru[] = "Форматирование";
char const formating_ko[] = "포멧";
char const formating_ja[] = "フォーマット";
char const formating_spa[] = "Formatear";
char const formating_tu[] = "Format";
char const formating_he[] = "פורמט";
char const formating_th[] = "รูปแบบ";
char const formating_po[] = "Format";

char const version_cns[] = "软件版本";
char const version_cnt[] = "軟件版本";
char const version_en[] = "Version";
char const version_ru[] = "Версия";
char const version_ko[] = "버전";
char const version_ja[] = "バージョン";
char const version_spa[] = "Version";
char const version_tu[] = "Versiyon";
char const version_he[] = "גרסה";
char const version_th[] = "รุ่น";
char const version_po[] = "Wersja";

char const version[] = VERSION_NUM;

char const tv_mode_cns[] = " TV";
char const tv_mode_cnt[] = " TV";
char const tv_mode_en[] =  " TV";
char const tv_mode_ru[] =  " TV";
char const tv_mode_ko[] =  " TV";
char const tv_mode_ja[] =  " TV";
char const tv_mode_spa[] = " TV";
char const tv_mode_tu[] = " TV";
char const tv_mode_he[] = " TV";
char const tv_mode_th[] = " TV";
char const tv_mode_po[] = " TV";

char const ntsc_cns[] = "NTSC";
char const ntsc_cnt[] = "NTSC";
char const ntsc_en[] =  "NTSC";
char const ntsc_ru[] =  "NTSC";
char const ntsc_ko[] =  "NTSC";
char const ntsc_ja[] =  "NTSC";
char const ntsc_spa[] = "NTSC";
char const ntsc_tu[] = "NTSC";
char const ntsc_he[] = "NTSC";
char const ntsc_th[] = "NTSC";
char const ntsc_po[] = "NTSC";

char const pal_cns[] = "PAL";
char const pal_cnt[] = "PAL";
char const pal_en[] =  "PAL";
char const pal_ru[] =  "PAL";
char const pal_ko[] =  "PAL";
char const pal_ja[] =  "PAL";
char const pal_spa[] = "PAL";
char const pal_tu[] = "PAL";
char const pal_he[] = "PAL";
char const pal_th[] = "PAL";
char const pal_po[] = "PAL";

char const r1280X1024[] = "1.3M 1280X1024";
char const r720X480[] = "720X480";
char const vga640X480[] = "VGA 640X480";
char const qvga320X240[] = "QVGA 320X240";
char const r1280X720[] = "1280X720";
char const r1920X1080[] = "1920X1080";
char const r2560X1440[] = "2560X1440";
char const r4032X3024[] = "4032X3024";

char const resolution_cns[] = "分辨率";
char const resolution_cnt[] = "分辨率";
char const resolution_en[] = "Resolution";
char const resolution_ru[] = "Коэффициент различения";
char const resolution_ko[] = "해상도";
char const resolution_ja[] = "解像度";
char const resolution_spa[] = "Resolucion";
char const resolution_tu[] = "Resolucion";
char const resolution_he[] = "רזולוציה";
char const resolution_th[] = "เจอภาพ";
char const resolution_po[] = "Rozkład";

char const loop_video_cns[] = "循环摄像";
char const loop_video_cnt[] = "循環攝像";
char const loop_video_en[] = "Cyclic Record";
char const loop_video_ru[] = "Цикл. сьёмка";
char const loop_video_ko[] = "사이클 리코딩";
char const loop_video_ja[] = "循環録画";
char const loop_video_spa[] = "Grabacion video circulante";
char const loop_video_tu[] = "Döngüsel Kayıt";
char const loop_video_he[] = "הקלטה מחזורית";
char const loop_video_th[] = "เวลาภาพ";
char const loop_video_po[] = "Nagrywanie cykliczne";

char const motion_detecting_cns[] = "移动侦测";
char const motion_detecting_cnt[] = "移動偵測";
char const motion_detecting_en[] = "Motion Detection";
char const motion_detecting_ru[] = "Обнаружение движения";
char const motion_detecting_ko[] = "모션 검출";
char const motion_detecting_ja[] = "移動監視";
char const motion_detecting_spa[] = "Deteccion movible";
char const motion_detecting_tu[] = "Hareket Algılama";
char const motion_detecting_he[] = "חיישן תנועה";
char const motion_detecting_th[] = "การตรวจจับภาพ";
char const motion_detecting_po[] = "Detekcja ruchu";

char const audio_recording_cns[] = "录音功能";
char const audio_recording_cnt[] = "錄音功能";
char const audio_recording_en[] = "Audio";
char const audio_recording_ru[] = "Запись";
char const audio_recording_ko[] = "녹음";
char const audio_recording_ja[] = "録音";
char const audio_recording_spa[] = "Grabacion sonido";
char const audio_recording_tu[] = "Kayıt";
char const audio_recording_he[] = "אודיו";
char const audio_recording_th[] = "บันทึกเสียง";
char const audio_recording_po[] = "Nagranie";

char const date_tag_cns[] = "时间标志";
char const date_tag_cnt[] = "時間標誌";
char const date_tag_en[] = "Date Tag";
char const date_tag_ru[] = "Заметка времени";
char const date_tag_ko[] = "타임 태그";
char const date_tag_ja[] = "時間ラベル";
char const date_tag_spa[] = "Etiqueta hora";
char const date_tag_tu[] = "Zaman etiketi";
char const date_tag_he[] = "תיוג תאריך";
char const date_tag_th[] = "วันที่บันทึก";
char const date_tag_po[] = "Data etykieta";

char const night_visoin_cns[] = "补光灯";
char const night_visoin_cnt[] = "補光燈";
char const night_visoin_en[] = "Fill light";
char const night_visoin_ru[] = "Заполните свет";
char const night_visoin_ko[] = "빛을 채우기";
char const night_visoin_ja[] = "補助光";
char const night_visoin_spa[] = "Llena de luz";
char const night_visoin_tu[] = "Işık doldurun";
char const night_visoin_he[] = "אור המילוי";
char const night_visoin_th[] = "กรอกแสง";
char const night_visoin_po[] = "Wypełnij światłem";

char const gsensor_sens_cns[] = "重力感应";
char const gsensor_sens_cnt[] = "重力感應";
char const gsensor_sens_en[] =  "G SENSOR";
char const gsensor_sens_ru[] =  "гравитационная индукция";
char const gsensor_sens_ko[] =  "중력 센서";
char const gsensor_sens_ja[] =  "重力誘導";
char const gsensor_sens_spa[] = "La gravedad de la inducción";
char const gsensor_sens_tu[] = "Yerçekimi sensörü";
char const gsensor_sens_he[] = "חיישן הכבידה";
char const gsensor_sens_th[] = "เซ็นเซอร์แรงโน้มถ่วง";
char const gsensor_sens_po[] = "Gravity czujnik";

char const low_cns[] = "低";
char const low_cnt[] = "低";
char const low_en[] =  "low";
char const low_ru[] =  "низкий";
char const low_ko[] = "낮은";
char const low_ja[] =  "低い";
char const low_spa[] = "bajo";
char const low_tu[] = "düşük";
char const low_he[] = "נמוך";
char const low_th[] = "ต่ำ";
char const low_po[] = "niski";

char const mid_cns[] = "中";
char const mid_cnt[] = "中";
char const mid_en[] =  "mid";
char const mid_ru[] =  "середина";
char const mid_ko[] = "중간";
char const mid_ja[] =  "ミドル";
char const mid_spa[] = "medio";
char const mid_tu[] = "içinde";
char const mid_he[] = "ב";
char const mid_th[] = "ใน";
char const mid_po[] = "w";

char const high_cns[] = "高";
char const high_cnt[] = "高";
char const high_en[] =  "high";
char const high_ru[] =  "высокий";
char const high_ko[] = "고";
char const high_ja[] =  "高い";
char const high_spa[] = "alta";
char const high_tu[] = "yüksek";
char const high_he[] = "גבוה";
char const high_th[] = "สูง";
char const high_po[] = "wysoki";

char const two_sec_cns[] = "两秒";
char const two_sec_cnt[] = "兩秒";
char const two_sec_en[] = "2S";
char const two_sec_ru[] = "2 с.";
char const two_sec_ko[] = "2초";
char const two_sec_ja[] = "二秒";
char const two_sec_spa[] = "2 seg";
char const two_sec_tu[] = "2 saniye";
char const two_sec_he[] = "2 שניות";
char const two_sec_th[] = "2วินาที";
char const two_sec_po[] = "2 sekundy";

char const five_sec_cns[] = "五秒";
char const five_sec_cnt[] = "五秒";
char const five_sec_en[] = "5S";
char const five_sec_ru[] = "5 с.";
char const five_sec_ko[] = "5초";
char const five_sec_ja[] = "五秒";
char const five_sec_spa[] = "5 seg";
char const five_sec_tu[] = "5 saniye";
char const five_sec_he[] = "5 שניות";
char const five_sec_th[] = "5วินาที";
char const five_sec_po[] = "5 sekund";

char const fast_view_cns[] = "快速浏览";
char const fast_view_cnt[] = "快速瀏覽";
char const fast_view_en[] = "Fast View";
char const fast_view_ru[] = "Быстро просмотрить";
char const fast_view_ko[] = "훑어보기";
char const fast_view_ja[] = "急速ブラウズ";
char const fast_view_spa[] = "Visualizacion rapida";
char const fast_view_tu[] = "Hızlı Görünüm";
char const fast_view_he[] = "צפייה מהירה";
char const fast_view_th[] = "ความเร็ว";
char const fast_view_po[] = "Quick View";

char const delete_this_cns[] = "删除当前";
char const delete_this_cnt[] = "刪除當前";
char const delete_this_en[] = "Delete This";
char const delete_this_ru[] = "Удалить текущее";
char const delete_this_ko[] = "현단계 삭제";
char const delete_this_ja[] = "現在をディレートします";
char const delete_this_spa[] = "Borrar lo actual";
char const delete_this_tu[] = "Bu Sil";
char const delete_this_he[] = "מחק קובץ זה";
char const delete_this_th[] = "ลบอันเดียว";
char const delete_this_po[] = "Usuń prąd";

char const delete_all_cns[] = "删除所有";
char const delete_all_cnt[] = "刪除所有";
char const delete_all_en[] = "Delete All";
char const delete_all_ru[] = "Удалить все";
char const delete_all_ko[] = "전부 삭제";
char const delete_all_ja[] = "全部をディレートします";
char const delete_all_spa[] = "Borrar todo";
char const delete_all_tu[] = "Tümünü Sil";
char const delete_all_he[] = "מחק הכל";
char const delete_all_th[] = "ลบทั้งหมด";
char const delete_all_po[] = "Usuń wszystko";

char const lock_this_cns[] = "加锁当前";
char const lock_this_cnt[] = "加鎖當前";
char const lock_this_en[] = "Lock This";
char const lock_this_ru[] = "Блокировать текущее";
char const lock_this_ko[] = "현단계 라크";
char const lock_this_ja[] = "現在をロックします";
char const lock_this_spa[] = "Bloquear lo actual";
char const lock_this_tu[] = "Bu Lock";
char const lock_this_he[] = "נעל קובץ זה";
char const lock_this_th[] = "ล็อคอันเดียว";
char const lock_this_po[] = "Blokada prądu";

char const unlock_this_cns[] = "解锁当前";
char const unlock_this_cnt[] = "解鎖當前";
char const unlock_this_en[] = "Unlock This";
char const unlock_this_ru[] = "Разблокировать текущее ";
char const unlock_this_ko[] = "현단계 언라크";
char const unlock_this_ja[] = "現在をアンロックします";
char const unlock_this_spa[] = "Desbloquear lo actual";
char const unlock_this_tu[] = "Bu kilidini";
char const unlock_this_he[] = "בטל נעילה";
char const unlock_this_th[] = "โปรดล็อค";
char const unlock_this_po[] = "Odblokuj prądu";

char const lock_all_cns[] = "全部加锁";
char const lock_all_cnt[] = "全部加鎖";
char const lock_all_en[] = "Lock All";
char const lock_all_ru[] = "Блокировать  все";
char const lock_all_ko[] = "전부 라크";
char const lock_all_ja[] = "全部をロックします";
char const lock_all_spa[] = "Bloquear todo";
char const lock_all_tu[] = "Tümünü Kilit";
char const lock_all_he[] = "נעל הכל";
char const lock_all_th[] = "ล็อคทั้งหมด";
char const lock_all_po[] = "Wszystkie blokady";

char const unlock_all_cns[] = "全部解锁";
char const unlock_all_cnt[] = "全部解鎖";
char const unlock_all_en[] = "UnLock All";
char const unlock_all_ru[] = "Разблокировать все";
char const unlock_all_ko[] = "전부 언라크";
char const unlock_all_ja[] = "全部をアンロックします";
char const unlock_all_spa[] = "Desbloquear todo";
char const unlock_all_tu[] = "Tümünü kilidini";
char const unlock_all_he[] = "בטל כל הנעילות";
char const unlock_all_th[] = "โปรดล็อคทั้งหมด";
char const unlock_all_po[] = "Odblokować wszystkie";

char const delete_cns[] = "删除";
char const delete_cnt[] = "删除";
char const delete_en[] = "Delete";
char const delete_ru[] = "Удалить";
char const delete_ko[] = "삭제";
char const delete_ja[] = "ディレート";
char const delete_spa[] = "Borrar";
char const delete_tu[] = "Silmek";
char const delete_he[] = "מחק";
char const delete_th[] = "ลบ";
char const delete_po[] = "usunąć";

char const lock_cns[] = "加锁";
char const lock_cnt[] = "加鎖";
char const lock_en[] = "Lock";
char const lock_ru[] = "Блокировать";
char const lock_ko[] = "라크";
char const lock_ja[] = "ロック";
char const lock_spa[] = "Bloquear";
char const lock_tu[] = "Kilitleme";
char const lock_he[] = "נעל";
char const lock_th[] = "ล็อค";
char const lock_po[] = "Blokowanie";

char const setting_cns[] = "设置";
char const setting_cnt[] = "設置";
char const setting_en[] = "Setting";
char const setting_ru[] = "Настройка";
char const setting_ko[] = "설치";
char const setting_ja[] = "設定";
char const setting_spa[] = "Ajustar";
char const setting_tu[] = "Ayarlar";
char const setting_he[] = "הגדרות";
char const setting_th[] = "ตั้งค่า";
char const setting_po[] = "Utworzyć";

char const video_cns[] = "视频模式";
char const video_cnt[] = "視頻模式";
char const video_en[] = "Video";
char const video_ru[] = "Видео";
char const video_ko[] = "비디오";
char const video_ja[] = "ビデオ";
char const video_spa[] = "Video";
char const video_tu[] = "Video";
char const video_he[] = "וידאו";
char const video_th[] = "สัญญาณภาพออก";
char const video_po[] = "Wideo";

char const photo_cns[] = "拍照模式";
char const photo_cnt[] = "拍照模式";
char const photo_en[] = "Photo";
char const photo_ru[] = "фотографировать";
char const photo_ko[] = "카메라";
char const photo_ja[] = "撮影";
char const photo_spa[] = "Hace foto";
char const photo_tu[] = "Fotoğraf";
char const photo_he[] = "צילום תמונות ";
char const photo_th[] = "ถ่ายรูป";
char const photo_po[] = "Fotografia";

char const play_cns[] = "回放模式";
char const play_cnt[] = "回放模式";
char const play_en[] = "PlayBack";
char const play_ru[] = "Воспроизведение";
char const play_ko[] = "플레이백";
char const play_ja[] = "リプレイ";
char const play_spa[] = "Retroceder";
char const play_tu[] = "Playback";
char const play_he[] = "ניגון קבצים";
char const play_th[] = "ย้อนกลับ";
char const play_po[] = "Odtwarzanie";

char const wait_cns[] = "请稍后...";
char const wait_cnt[] = "請稍後...";
char const wait_en[] = "Please Waiting...";
char const wait_ru[] = "Пожалуйста, подождите …";
char const wait_ko[] = "기다려주세요...";
char const wait_ja[] = "少々お待ち下さい ...";
char const wait_spa[] = "Espere poco...";
char const wait_tu[] = "Lütfen Bekleme";
char const wait_he[] = "...המתן בבקשה";
char const wait_th[] = "โปรดรอ";
char const wait_po[] = "Proszę czekać...";


char const beep_sound_cns[] = "按键音";
char const beep_sound_cnt[] = "按鍵聲";
char const beep_sound_en[] = "Bepp sound";
char const beep_sound_ru[] = "Звуковой";
char const beep_sound_ko[] = "경고음";
char const beep_sound_ja[] = "ビープ音";
char const beep_sound_spa[] = "Sonido de pitido";
char const beep_sound_tu[] = "Bip sesi";
char const beep_sound_he[] = "צלצול התראה";
char const beep_sound_th[] = "เสียง";
char const beep_sound_po[] = "Dźwięk klawiszy";



char const *group_no_card[] = {
		"未插卡",
		"未插卡",
		"no card",
		"нет карты",
		"아무 카드도 없습니다",
		"カードなし",
		"Tarjta SD no online",
		"Bitiş kartı",
		"אין כרטיס",
		"ไม่มีการ์ด",
		"Brak karty"
};

//for format
char const *group_format_sd_ing[] = {
		"正在格式化...",
		"正在格式化...",
		"Formatting...",
		"форматирование...",
		"서식...",
		"書式設定...",
		"Formateo...",
		"Biçimlendirme ...",
		"עיצוב ...",
		"การจัดรูปแบบ ...",
		"Biçimlendirme ..."
};

char const *group_format_sd_succeed[] = {
		"格式化成功",
		"格式化成功",
		"Formatting success",
		"Форматирование успех",
		"서식 성공",
		"書式成功",
		"éxito Formateo",
		"Biçimlendirme başarı",
		"הצלחת עיצוב",
		"ความสำเร็จ",
		"Formatowanie sukces"
};

char const *group_format_sd_fail[] = {
		"格式化失败",
		"格式化失敗",
		"Formatting failed",
		"Форматирование не удалось",
		"포맷 실패",
		"書式設定に失敗しました",
		"no Formateo",
		"Biçimlendirme hatası",
		"כישלון עיצוב",
		"ความล้มเหลว",
		"awaria formatowanie"
};
//low power
char const *group_low_power[]= {
		"电量低",
		"電量低",
		"Low Power",
		"низкий",
		"배터리 부족",
		"ローバッテリ",
		"batería baja",
		"düşük pil",
		"סוללה חלשה",
		"ไฟต่ำ",
		"niski poziom baterii"
};
//lock
char const *group_file_lock[] = {
		"文件锁",
		"文件锁",
		"File is locked",
		"Карта SD не работает",
		"SD카드가 미접속상태임",
		"SDカードはオンラインではありません",
		"Tarjta SD no online",
		"dosya kilidi",
		"נעילת קובץ",
		"ล็อคไฟล์",
		"Blokada pliku"
};
//delete
char const *group_file_delete[] = {
		"请稍后...",
		"請稍後...",
		"Please Waiting...",
		"Пожалуйста, подождите …",
		"기다려주세요...",
		"少々お待ち下さい ...",
		"Espere poco...",
		"lütfen bekleyin ...",
		"...המתן בבקשה",
		"โปรดรอ...",
		"Proszę czekać …"
};



const ITEM_STRING language0   		= {{(u8*)simplified_chinese,	(u8*)simplified_chinese,	(u8*)simplified_chinese,	(u8*)simplified_chinese,	(u8*)simplified_chinese,	(u8*)simplified_chinese,(u8*)simplified_chinese,(u8*)simplified_chinese,(u8*)simplified_chinese,(u8*)simplified_chinese,(u8*)simplified_chinese}};
const ITEM_STRING language1   		= {{(u8*)traditional_chinese,	(u8*)traditional_chinese,	(u8*)traditional_chinese,(u8*)traditional_chinese,(u8*)traditional_chinese,(u8*)traditional_chinese,(u8*)traditional_chinese,(u8*)traditional_chinese,(u8*)traditional_chinese,(u8*)traditional_chinese,(u8*)traditional_chinese}};
const ITEM_STRING language2   		= {{(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english,	(u8*)english}};
const ITEM_STRING language3   		= {{(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian,	(u8*)russian}};
const ITEM_STRING language4   		= {{(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean,	(u8*)korean}};
const ITEM_STRING language5   		= {{(u8*)japanese,(u8*)japanese,	(u8*)japanese,(u8*)japanese,	(u8*)japanese,(u8*)japanese,	(u8*)japanese,(u8*)japanese,	(u8*)japanese,(u8*)japanese,	(u8*)japanese}};
const ITEM_STRING language6   		= {{(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish,(u8*)spanish}};
const ITEM_STRING language7   		= {{(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey,(u8*)turkey}};
const ITEM_STRING language8   		= {{(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew,(u8*)hebrew}};
const ITEM_STRING language9   		= {{(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai,(u8*)thai}};
const ITEM_STRING language10   		= {{(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish,(u8*)polish}};

const ITEM_STRING power_off_string0   = {{(u8*)off_cns,			(u8*)off_cnt,		(u8*)off_en,		(u8*)off_ru,		(u8*)off_ko,		(u8*)off_ja,		(u8*)off_spa,		(u8*)off_tu,		(u8*)off_he,		(u8*)off_th,		(u8*)off_po }};
const ITEM_STRING power_off_string1   = {{(u8*)one_minute_cns,		(u8*)one_minute_cnt,	(u8*)one_minute_en,	 (u8*)one_minute_ru,	(u8*)one_minute_ko,(u8*)one_minute_ja,	(u8*)one_minute_spa ,	(u8*)one_minute_tu,	(u8*)one_minute_he,	(u8*)one_minute_th,	(u8*)one_minute_po}};
const ITEM_STRING power_off_string2   = {{(u8*)three_minute_cns,	(u8*)three_minute_cnt, 	(u8*)three_minute_en,(u8*)three_minute_ru, (u8*)three_minute_ko,(u8*)three_minute_ja, (u8*)three_minute_spa, (u8*)three_minute_tu, (u8*)three_minute_he, (u8*)three_minute_th, (u8*)three_minute_po }};
const ITEM_STRING light_source_string0  = {{(u8*)fre_50hz_cns,		(u8*)fre_50hz_cns, 	(u8*)fre_50hz_cns ,	(u8*)fre_50hz_cns, 	(u8*)fre_50hz_cns ,	(u8*)fre_50hz_cns, 	(u8*)fre_50hz_cns, 	(u8*)fre_50hz_cns, 	(u8*)fre_50hz_cns, 	(u8*)fre_50hz_cns, 	(u8*)fre_50hz_cns }};
const ITEM_STRING light_source_string1  = {{(u8*)fre_60hz_cns,		(u8*)fre_60hz_cns, 	(u8*)fre_60hz_cns ,	(u8*)fre_60hz_cns, 	(u8*)fre_60hz_cns ,	(u8*)fre_60hz_cns, 	(u8*)fre_60hz_cns , 	(u8*)fre_60hz_cns , 	(u8*)fre_60hz_cns , 	(u8*)fre_60hz_cns , 	(u8*)fre_60hz_cns }};
const ITEM_STRING sleep_time_string0   = {{(u8*)off_cns,			(u8*)off_cnt, 		(u8*)off_en,		(u8*)off_ru, 		(u8*)off_ko,		(u8*)off_ja, 		(u8*)off_spa, 		(u8*)off_tu, 		(u8*)off_he, 		(u8*)off_th, 		(u8*)off_po }};
const ITEM_STRING sleep_time_string1   = {{(u8*)one_minute_cns,	(u8*)one_minute_cnt, 	(u8*)one_minute_en,		(u8*)one_minute_ru, 	(u8*)one_minute_ko,		(u8*)one_minute_ja, 	(u8*)one_minute_spa, 	(u8*)one_minute_tu, 	(u8*)one_minute_he, 	(u8*)one_minute_th, 	(u8*)one_minute_po }};
const ITEM_STRING sleep_time_string2   = {{(u8*)three_minute_cns, 	(u8*)three_minute_cnt,	(u8*)three_minute_en ,	(u8*)three_minute_ru,	(u8*)three_minute_ko ,	(u8*)three_minute_ja,	(u8*)three_minute_spa,	(u8*)three_minute_tu,	(u8*)three_minute_he,	(u8*)three_minute_th,	(u8*)three_minute_po }};
const ITEM_STRING sleep_time_string3   = {{(u8*)five_minute_cns,	(u8*)five_minute_cnt,	(u8*)five_minute_en ,	(u8*)five_minute_ru,	(u8*) five_minute_ko ,	(u8*)five_minute_ja,	(u8*) five_minute_spa,	(u8*) five_minute_tu,	(u8*) five_minute_he,	(u8*) five_minute_th,	(u8*) five_minute_po }};
const ITEM_STRING formate_string0   = {{(u8*)cancel_cns, 			(u8*)cancel_cnt,		(u8*)cancel_en,		(u8*)cancel_ru,		(u8*)cancel_ko,		(u8*)cancel_ja,		(u8*)cancel_spa,		(u8*)cancel_tu,		(u8*)cancel_he,		(u8*)cancel_th,		(u8*)cancel_po}};
const ITEM_STRING formate_string1   = {{(u8*)ok_cns, 				(u8*)ok_cnt, 		(u8*)ok_en,			(u8*)ok_ru, 		(u8*)ok_ko,				(u8*)ok_ja, 		(u8*)ok_spa, 		(u8*)ok_tu, 		(u8*)ok_he, 		(u8*)ok_th, 		(u8*)ok_po}};
const ITEM_STRING default_string0   = {{(u8*)cancel_cns, 			(u8*)cancel_cnt,	(u8*)cancel_en ,	(u8*)cancel_ru,		(u8*)cancel_ko ,		(u8*)cancel_ja,		(u8*)cancel_spa,		(u8*)cancel_tu,		(u8*)cancel_he,		(u8*)cancel_th,		(u8*)cancel_po }};
const ITEM_STRING default_string1   = {{(u8*)ok_cns,				(u8*)ok_cnt, 		(u8*)ok_en ,		(u8*)ok_ru, 		(u8*)ok_ko ,			(u8*)ok_ja, 		(u8*)ok_spa , 		(u8*)ok_tu, 		(u8*)ok_he, 		(u8*)ok_th, 		(u8*)ok_po}};
const ITEM_STRING version_string0   = {{(u8*)version,				(u8*)version,		(u8*) version,		(u8*)version,		(u8*) version,			(u8*)version,		(u8*) version,		(u8*) version,		(u8*) version,		(u8*) version,		(u8*) version }};
const ITEM_STRING tv_string0   = {{(u8*)off_cns,	(u8*)off_cnt, 	(u8*)off_en ,	(u8*)off_ru, 	(u8*)off_ko , (u8*)off_ja,  (u8*)off_spa,  (u8*)off_tu,  (u8*)off_he,  (u8*)off_th,  (u8*)off_po }};
const ITEM_STRING tv_string1   = {{(u8*)ntsc_cns,	(u8*)ntsc_cnt, 	(u8*)ntsc_en ,	(u8*)ntsc_ru, 	(u8*)ntsc_ko , (u8*)ntsc_ja,  (u8*)ntsc_spa,  (u8*)ntsc_tu,  (u8*)ntsc_he,  (u8*)ntsc_th,  (u8*)ntsc_po }};
const ITEM_STRING tv_string2   = {{(u8*)pal_cns,	(u8*)pal_cnt, 	(u8*)pal_en ,	(u8*)pal_ru, 	(u8*)pal_ko , (u8*)pal_ja,  (u8*)pal_spa,  (u8*)pal_tu,  (u8*)pal_he,  (u8*)pal_th,  (u8*)pal_po }};
const ITEM_STRING attribute_page_string0  = {{(u8*)formating_cns,	(u8*)formating_cnt,	(u8*) formating_en,		(u8*)formating_ru,	(u8*) formating_ko,		(u8*)formating_ja,	(u8*) formating_spa,	(u8*) formating_tu,	(u8*) formating_he,	(u8*) formating_th,	(u8*) formating_po} };
const ITEM_STRING attribute_page_string1  = {{(u8*)lanuage_setting_cns,(u8*)lanuage_setting_cnt, 	(u8*) lanuage_setting_en,	(u8*)lanuage_setting_ru, 	(u8*) lanuage_setting_ko,	(u8*)lanuage_setting_ja, 	(u8*) lanuage_setting_spa, 	(u8*) lanuage_setting_tu, 	(u8*) lanuage_setting_he, 	(u8*) lanuage_setting_th, 	(u8*) lanuage_setting_po}};
const ITEM_STRING attribute_page_string2  = {{(u8*)auto_off_cns,	(u8*)auto_off_cnt, 	(u8*)auto_off_en,	(u8*)auto_off_ru, 	(u8*)auto_off_ko,		(u8*)auto_off_ja, 	(u8*)auto_off_spa, 	(u8*)auto_off_tu, 	(u8*)auto_off_he, 	(u8*)auto_off_th, 	(u8*)auto_off_po}};
const ITEM_STRING attribute_page_string3  = {{(u8*)screen_protecting_cns,(u8*)screen_protecting_cnt, 	(u8*)screen_protecting_en,	(u8*)screen_protecting_ru, 	(u8*)screen_protecting_ko,(u8*)screen_protecting_ja, 	(u8*)screen_protecting_spa, 	(u8*)screen_protecting_tu, 	(u8*)screen_protecting_he, 	(u8*)screen_protecting_th, 	(u8*)screen_protecting_po }};
const ITEM_STRING attribute_page_string4  = {{(u8*)defaulting_cns,	(u8*)defaulting_cnt,(u8*)defaulting_en ,	(u8*)defaulting_ru,	(u8*)defaulting_ko ,	(u8*)defaulting_ja, (u8*)defaulting_spa, (u8*)defaulting_tu, (u8*)defaulting_he, (u8*)defaulting_th, (u8*)defaulting_po }};

const ITEM_STRING attribute_page_string5  = {{(u8*) light_freq_cns,	(u8*)light_freq_cnt, 		(u8*)light_freq_en,			(u8*)light_freq_ru, 		(u8*)light_freq_ko,			(u8*)light_freq_ja, 		(u8*)light_freq_spa, 		(u8*)light_freq_tu, 		(u8*)light_freq_he, 		(u8*)light_freq_th, 		(u8*)light_freq_po }};
const ITEM_STRING attribute_page_string6  = {{(u8*)date_time_cns, 	(u8*)date_time_cnt, (u8*)date_time_en,	(u8*)date_time_ru,  (u8*)date_time_ko,		(u8*)date_time_ja,	(u8*)date_time_spa,	(u8*)date_time_tu,	(u8*)date_time_he,	(u8*)date_time_th,	(u8*)date_time_po }};
const ITEM_STRING attribute_page_string7  = {{(u8*) Picture_rotating_cns,(u8*)Picture_rotating_cnt, 	(u8*)Picture_rotating_en ,	(u8*)Picture_rotating_ru, 	(u8*)Picture_rotating_ko ,(u8*)Picture_rotating_ja, 	(u8*)Picture_rotating_spa, 	(u8*)Picture_rotating_tu, 	(u8*)Picture_rotating_he, 	(u8*)Picture_rotating_th, 	(u8*)Picture_rotating_po }};
const ITEM_STRING attribute_page_string8  = {{(u8*)version_cns,	(u8*)version_cnt, 	(u8*)version_en,	(u8*)version_ru, 	(u8*)version_ko,		(u8*)version_ja, 	(u8*)version_spa, 	(u8*)version_tu, 	(u8*)version_he, 	(u8*)version_th, 	(u8*)version_po}};
const ITEM_STRING attribute_page_string9  = {{(u8*) night_visoin_cns,	(u8*)night_visoin_cnt, 	(u8*)night_visoin_en,(u8*)night_visoin_ru, 	(u8*)night_visoin_ko,	(u8*)night_visoin_ja, 	(u8*)night_visoin_spa, 	(u8*)night_visoin_tu, 	(u8*)night_visoin_he, 	(u8*)night_visoin_th, 	(u8*)night_visoin_po}};

const ITEM_STRING attribute_beep_sound_string  = {{(u8*)beep_sound_cns,	(u8*)beep_sound_cnt, 	(u8*)beep_sound_en,	(u8*)beep_sound_ru, 	(u8*)beep_sound_ko,		(u8*)beep_sound_ja, 	(u8*)beep_sound_spa, 	(u8*)beep_sound_tu, 	(u8*)beep_sound_he, 	(u8*)beep_sound_th, 	(u8*)beep_sound_po}};
const ITEM_STRING attribute_tv_mode_string  = {{(u8*)tv_mode_cns,	(u8*)tv_mode_cnt, 	(u8*)tv_mode_en,	(u8*)tv_mode_ru, 	(u8*)tv_mode_ko,		(u8*)tv_mode_ja, 	(u8*)tv_mode_spa, 	(u8*)tv_mode_tu, 	(u8*)tv_mode_he, 	(u8*)tv_mode_th, 	(u8*)tv_mode_po}};
const ITEM_STRING video_resolution_string0   = {{(u8*)r720X480, 	(u8*)r720X480, 		(u8*)r720X480 ,		(u8*)r720X480, 		(u8*)r720X480 ,		(u8*)r720X480, 		(u8*)r720X480, 		(u8*)r720X480, 		(u8*)r720X480, 		(u8*)r720X480, 		(u8*)r720X480 }};
const ITEM_STRING video_resolution_string1   = {{(u8*)vga640X480,	(u8*)vga640X480, 	(u8*)vga640X480 ,	(u8*)vga640X480, 	(u8*)vga640X480 ,	(u8*)vga640X480, 	(u8*)vga640X480 , 	(u8*)vga640X480, 	(u8*)vga640X480, 	(u8*)vga640X480, 	(u8*)vga640X480}};
const ITEM_STRING video_resolution_string2   = {{(u8*)r1920X1080,	(u8*)r1920X1080,	(u8*)r1920X1080,	(u8*)r1920X1080,	(u8*)r1920X1080,	(u8*)r1920X1080,	(u8*)r1920X1080 ,	(u8*)r1920X1080,	(u8*)r1920X1080,	(u8*)r1920X1080,	(u8*)r1920X1080}};
const ITEM_STRING video_resolution_string3   = {{(u8*)r1280X720,	(u8*)r1280X720,	(u8*)r1280X720,		(u8*)r1280X720,		(u8*)r1280X720,		(u8*)r1280X720,		(u8*)r1280X720,		(u8*)r1280X720,		(u8*)r1280X720,		(u8*)r1280X720,		(u8*)r1280X720 }};

const ITEM_STRING video_loop_string0   = {{(u8*)off_cns,			(u8*)off_cnt,  		(u8*)off_en,		(u8*)off_ru,  		(u8*)off_ko,	(u8*)off_ja,  		(u8*)off_spa,  		(u8*)off_tu,  		(u8*)off_he,  		(u8*)off_th,  		(u8*)off_po}};
const ITEM_STRING video_loop_string1   = {{(u8*)three_minute_cns, 	(u8*)three_minute_cnt,	(u8*)three_minute_en,	(u8*)three_minute_ru,	(u8*)three_minute_ko ,	(u8*)three_minute_ja,	(u8*)three_minute_spa,	(u8*)three_minute_tu,	(u8*)three_minute_he,	(u8*)three_minute_th,	(u8*)three_minute_po}};
const ITEM_STRING video_loop_string2   = {{(u8*)five_minute_cns, 	(u8*)five_minute_cnt,	(u8*)five_minute_en,	(u8*)five_minute_ru,	(u8*)five_minute_ko ,	(u8*)five_minute_ja,	(u8*) five_minute_spa,	(u8*) five_minute_tu,	(u8*) five_minute_he,	(u8*) five_minute_th,	(u8*) five_minute_po}};
const ITEM_STRING video_loop_string3   = {{(u8*)ten_minute_cns,	(u8*)ten_minute_cnt, 	(u8*)ten_minute_en ,	(u8*)ten_minute_ru,		(u8*)ten_minute_ko ,	(u8*)ten_minute_ja,		(u8*) ten_minute_spa,		(u8*) ten_minute_tu,		(u8*) ten_minute_he,		(u8*) ten_minute_th,		(u8*) ten_minute_po}};
const ITEM_STRING off_string   		= {{(u8*)off_cns,	(u8*)off_cnt, 	(u8*)off_en,	(u8*)off_ru,  	(u8*)off_ko,	(u8*)off_ja,  	(u8*)off_spa,  	(u8*)off_tu,  	(u8*)off_he,  	(u8*)off_th,  	(u8*)off_po}};
const ITEM_STRING on_string   			= {{(u8*)on_cns,	(u8*)on_cnt,	(u8*)on_en,		(u8*)on_ru,		(u8*)on_ko,		(u8*)on_ja,		(u8*)on_spa,		(u8*)on_tu,		(u8*)on_he,		(u8*)on_th,		(u8*)on_po}};
const ITEM_STRING video_detecting_string0   = {{(u8*)off_cns,	(u8*)off_cnt, 	(u8*)off_en,	(u8*)off_ru,  	(u8*)off_ko,	(u8*)off_ja,  	(u8*)off_spa,  	(u8*)off_tu,  	(u8*)off_he,  	(u8*)off_th,  	(u8*)off_po}};
const ITEM_STRING video_detecting_string1   = {{(u8*)on_cns,	(u8*)on_cnt, 	(u8*)on_en,		(u8*)on_ru,		(u8*)on_ko,		(u8*)on_ja,		(u8*)on_spa,		(u8*)on_tu,		(u8*)on_he,		(u8*)on_th,		(u8*)on_po}};
const ITEM_STRING video_voice_string0  = {{(u8*)off_cns,		(u8*)off_cnt,	(u8*)off_en,	(u8*)off_ru,  	(u8*)off_ko,	(u8*)off_ja,  	(u8*)off_spa,  	(u8*)off_tu,  	(u8*)off_he,  	(u8*)off_th,  	(u8*)off_po}};
const ITEM_STRING video_voice_string1  = {{(u8*)on_cns,		(u8*)on_cnt, 	(u8*)on_en,		(u8*)on_ru,		(u8*)on_ko,		(u8*)on_ja,		(u8*)on_spa,		(u8*)on_tu,		(u8*)on_he,		(u8*)on_th,		(u8*)on_po}};
const ITEM_STRING video_date_string0   = {{(u8*)off_cns,		(u8*)off_cnt, 	(u8*)off_en,	(u8*)off_ru,  	(u8*)off_ko,	(u8*)off_ja,  	(u8*)off_spa,  	(u8*)off_tu,  	(u8*)off_he,  	(u8*)off_th,  	(u8*)off_po}};
const ITEM_STRING video_date_string1   = {{(u8*)on_cns, 		(u8*)on_cnt,	(u8*)on_en ,	(u8*)on_ru,		(u8*)on_ko,		(u8*)on_ja,		(u8*)on_spa,		(u8*)on_tu,		(u8*)on_he,		(u8*)on_th,		(u8*)on_po}};
const ITEM_STRING video_night_string0  = {{(u8*)off_cns,		(u8*)off_cnt,	(u8*)off_en,	(u8*)off_ru,  	(u8*)off_ko,	(u8*)off_ja,  	(u8*)off_spa,  	(u8*)off_tu,  	(u8*)off_he,  	(u8*)off_th,  	(u8*)off_po}};
const ITEM_STRING video_night_string1  = {{(u8*)on_cns,		(u8*)on_cnt, 	(u8*)on_en,		(u8*)off_ru,  	(u8*)off_ko,	(u8*)off_ja,  	(u8*)off_spa,  	(u8*)off_tu,  	(u8*)off_he,  	(u8*)off_th,  	(u8*)off_po}};
const ITEM_STRING video_gsensor_string0  = {{(u8*)off_cns,	(u8*)off_cnt, (u8*)off_en, (u8*)off_ru,  (u8*)off_ko, (u8*)off_ja,  (u8*)off_spa,  (u8*)off_tu,  (u8*)off_he,  (u8*)off_th,  (u8*)off_po}};
const ITEM_STRING video_gsensor_string1  = {{(u8*)low_cns,	(u8*)low_cnt, (u8*)low_en, (u8*)low_ru,  (u8*)low_ko, (u8*)low_ja,  (u8*)low_spa,  (u8*)low_tu,  (u8*)low_he,  (u8*)low_th,  (u8*)low_po}};
const ITEM_STRING video_gsensor_string2  = {{(u8*)mid_cns,	(u8*)mid_cnt, (u8*)mid_en, (u8*)mid_ru,  (u8*)mid_ko, (u8*)mid_ja,  (u8*)mid_spa,  (u8*)mid_tu,  (u8*)mid_he,  (u8*)mid_th,  (u8*)mid_po}};
const ITEM_STRING video_gsensor_string3  = {{(u8*)high_cns,(u8*)high_cnt,(u8*)high_en,(u8*)high_ru, (u8*)high_ko, (u8*)high_ja,(u8*)high_spa,(u8*)high_tu,(u8*)high_he,(u8*)high_th,(u8*)high_po}};
const ITEM_STRING video_setting_string0  = {{(u8*) resolution_cns, 	(u8*)resolution_cnt,	(u8*)resolution_en,	(u8*)resolution_ru,	(u8*)resolution_ko,(u8*)resolution_ja,	(u8*)resolution_spa,	(u8*)resolution_tu,	(u8*)resolution_he,	(u8*)resolution_th,	(u8*)resolution_po }};
const ITEM_STRING video_setting_string1  = {{(u8*) date_tag_cns,		(u8*)date_tag_cnt, 		(u8*)date_tag_en ,	 (u8*)date_tag_ru, 		(u8*)date_tag_ko , 		(u8*)date_tag_ja, 		(u8*)date_tag_spa, 		(u8*)date_tag_tu, 		(u8*)date_tag_he, 		(u8*)date_tag_th, 		(u8*)date_tag_po }};
const ITEM_STRING video_setting_string2  = {{(u8*)motion_detecting_cns,(u8*) motion_detecting_cnt,	(u8*)motion_detecting_en ,	(u8*) motion_detecting_ru,	(u8*)motion_detecting_ko ,	(u8*) motion_detecting_ja,(u8*)motion_detecting_spa,(u8*)motion_detecting_tu,(u8*)motion_detecting_he,(u8*)motion_detecting_th,(u8*)motion_detecting_po }};
const ITEM_STRING video_setting_string3  = {{(u8*) loop_video_cns, 	(u8*)loop_video_cnt,	(u8*)loop_video_en,	(u8*)loop_video_ru,	(u8*)loop_video_ko,(u8*)loop_video_ja,	(u8*)loop_video_spa,	(u8*)loop_video_tu,	(u8*)loop_video_he,	(u8*)loop_video_th,	(u8*)loop_video_po}};
const ITEM_STRING video_setting_string4  = {{(u8*) audio_recording_cns,(u8*)audio_recording_cnt,	(u8*)audio_recording_en,	(u8*)audio_recording_ru,	(u8*)audio_recording_ko, 	(u8*)audio_recording_ja,  (u8*)audio_recording_spa,  (u8*)audio_recording_tu,  (u8*)audio_recording_he,  (u8*)audio_recording_th,  (u8*)audio_recording_po}};
const ITEM_STRING video_setting_string6  = {{(u8*)gsensor_sens_cns,(u8*)gsensor_sens_cnt, (u8*)gsensor_sens_en,(u8*)gsensor_sens_ru, (u8*)gsensor_sens_ko,	(u8*)gsensor_sens_ja, 	(u8*)gsensor_sens_spa, 	(u8*)gsensor_sens_tu, 	(u8*)gsensor_sens_he, 	(u8*)gsensor_sens_th, 	(u8*)gsensor_sens_po}};
const ITEM_STRING photo_resolution_string0   = {{(u8*)r1280X720,		(u8*)r1280X720, 			(u8*)r1280X720,		(u8*)r1280X720, 		(u8*)r1280X720,		(u8*)r1280X720, 	 	(u8*)r1280X720, 	 	(u8*)r1280X720, 	 	(u8*)r1280X720, 	 	(u8*)r1280X720, 	 	(u8*)r1280X720}};
const ITEM_STRING photo_resolution_string1   = {{(u8*)vga640X480,		(u8*)vga640X480, 		(u8*)vga640X480 ,	(u8*)vga640X480, 	(u8*)vga640X480 ,	(u8*)vga640X480, 	(u8*)vga640X480 , 	(u8*)vga640X480, 	(u8*)vga640X480, 	(u8*)vga640X480, 	(u8*)vga640X480}};
const ITEM_STRING photo_resolution_string2   = {{(u8*)r1920X1080,		(u8*)r1920X1080, 		(u8*)r1920X1080 ,	(u8*)r1920X1080, 	(u8*)r1920X1080 ,	(u8*)r1920X1080, 	(u8*)r1920X1080, 	(u8*)r1920X1080, 	(u8*)r1920X1080, 	(u8*)r1920X1080, 	(u8*)r1920X1080 }};
const ITEM_STRING photo_resolution_string3   = {{(u8*)r2560X1440,		(u8*)r2560X1440, 		(u8*)r2560X1440 ,	(u8*)r2560X1440, 	(u8*)r2560X1440 ,	(u8*)r2560X1440, 	(u8*)r2560X1440, 	(u8*)r2560X1440, 	(u8*)r2560X1440, 	(u8*)r2560X1440, 	(u8*)r2560X1440 }};
const ITEM_STRING rotate_string0             = {{(u8*)cancel_cns,	(u8*)cancel_cnt, 	(u8*)cancel_en ,	(u8*)cancel_ru, (u8*)cancel_ko ,(u8*)cancel_ja, 	(u8*)cancel_spa, 	(u8*)cancel_tu, 	(u8*)cancel_he, 	(u8*)cancel_th, 	(u8*)cancel_po }};
const ITEM_STRING rotate_string1   		  = {{(u8*)ok_cns,		(u8*)ok_cnt,		(u8*)ok_en,			(u8*)ok_ru,		(u8*)ok_ko,		(u8*)ok_ja,		(u8*)ok_spa,		(u8*)ok_tu,		(u8*)ok_he,		(u8*)ok_th,		(u8*)ok_po }};
const ITEM_STRING photo_view_string0  		 = {{(u8*)off_cns,		(u8*)off_cnt,		(u8*)off_en,		(u8*)off_ru,  	(u8*)off_ko,	(u8*)off_ja,  	(u8*)off_spa,  	(u8*)off_tu,  	(u8*)off_he,  	(u8*)off_th,  	(u8*)off_po}};
const ITEM_STRING photo_view_string1  		 = {{(u8*)two_sec_cns,	(u8*)two_sec_cnt,	(u8*)two_sec_en,	(u8*)two_sec_ru,	(u8*)two_sec_ko,	(u8*)two_sec_ja,	(u8*)two_sec_spa,	(u8*)two_sec_tu,	(u8*)two_sec_he,	(u8*)two_sec_th,	(u8*)two_sec_po}};
const ITEM_STRING photo_view_string2   	= {{(u8*)five_sec_cns,	(u8*)five_sec_cnt,	(u8*)five_sec_en ,	(u8*)five_sec_ru,	(u8*)five_sec_ko ,	(u8*)five_sec_ja,	(u8*)five_sec_spa,	(u8*)five_sec_tu,	(u8*)five_sec_he,	(u8*)five_sec_th,	(u8*)five_sec_po }};
const ITEM_STRING photo_date_string0   	= {{(u8*)off_cns,		(u8*)off_cnt,		(u8*)off_en,		(u8*)off_ru,		(u8*)off_ko,		(u8*)off_ja,		(u8*)off_spa,		(u8*)off_tu,		(u8*)off_he,		(u8*)off_th,		(u8*)off_po} };
const ITEM_STRING photo_date_string1   	= {{(u8*)on_cns, 		(u8*)on_cnt,		(u8*)on_en,			(u8*)on_ru,			(u8*)on_ko,			(u8*)on_ja,			(u8*)on_spa,			(u8*)on_tu,			(u8*)on_he,			(u8*)on_th,			(u8*)on_po}};
const ITEM_STRING photo_setting_string0  	= {{(u8*)resolution_cns, 	(u8*)resolution_cnt,	(u8*)resolution_en ,(u8*) resolution_ru,(u8*)resolution_ko,	(u8*) resolution_ja,(u8*)resolution_spa,(u8*)resolution_tu,(u8*)resolution_he,(u8*)resolution_th,(u8*)resolution_po }};
const ITEM_STRING photo_setting_string1  	= {{(u8*)fast_view_cns,		(u8*)fast_view_cnt, 	(u8*)fast_view_en , (u8*)fast_view_ru, 	(u8*)fast_view_ko,	(u8*)fast_view_ja, 	(u8*)fast_view_spa, 	(u8*)fast_view_tu, 	(u8*)fast_view_he, 	(u8*)fast_view_th, 	(u8*)fast_view_po }};
const ITEM_STRING photo_setting_string2  	= {{(u8*)date_tag_cns,		(u8*)date_tag_cnt, 		(u8*)date_tag_en,	(u8*)date_tag_ru, 	(u8*)date_tag_ko,	(u8*)date_tag_ja, 	(u8*)date_tag_spa, 	(u8*)date_tag_tu, 	(u8*)date_tag_he, 	(u8*)date_tag_th, 	(u8*)date_tag_po}};
const ITEM_STRING photo_deleting_string0  	= {{(u8*)delete_this_cns,	(u8*)delete_this_cnt,	(u8*)delete_this_en,(u8*)delete_this_ru,	(u8*)delete_this_ko,	(u8*)delete_this_ja,	(u8*)delete_this_spa,	(u8*)delete_this_tu,	(u8*)delete_this_he,	(u8*)delete_this_th,	(u8*)delete_this_po}};
const ITEM_STRING photo_deleting_string1  	= {{(u8*)delete_all_cns,	(u8*)delete_all_cnt, 	(u8*)delete_all_en,	(u8*)delete_all_ru, 	(u8*)delete_all_ko,		(u8*)delete_all_ja, 	(u8*)delete_all_spa, 	(u8*)delete_all_tu, 	(u8*)delete_all_he, 	(u8*)delete_all_th, 	(u8*)delete_all_po}};
const ITEM_STRING cancel_string  			= {{(u8*)cancel_cns,		(u8*)cancel_cnt,		(u8*)cancel_en,		(u8*)cancel_ru,	(u8*)cancel_ko,		(u8*)cancel_ja,	(u8*)cancel_spa,	(u8*)cancel_tu,	(u8*)cancel_he,	(u8*)cancel_th,	(u8*)cancel_po }};
const ITEM_STRING ok_string 	  			= {{(u8*)ok_cns,	   (u8*)ok_cnt,		(u8*)ok_en,	(u8*)ok_ru,			(u8*)ok_ko,			(u8*)ok_ja,			(u8*)ok_spa,			(u8*)ok_tu,			(u8*)ok_he,			(u8*)ok_th,			(u8*)ok_po}};
const ITEM_STRING photo_protecting_string0   = {{(u8*)lock_this_cns, 	(u8*)lock_this_cnt,		(u8*)lock_this_en , (u8*)lock_this_ru,	(u8*)lock_this_ko , (u8*)lock_this_ja,	(u8*)lock_this_spa,	(u8*)lock_this_tu,	(u8*)lock_this_he,	(u8*)lock_this_th,	(u8*)lock_this_po }};
const ITEM_STRING photo_protecting_string1   = {{(u8*)unlock_this_cns, (u8*)unlock_this_cnt, 	(u8*)unlock_this_en,(u8*)unlock_this_ru,(u8*)unlock_this_ko,(u8*)unlock_this_ja,(u8*)unlock_this_spa,(u8*)unlock_this_tu,(u8*)unlock_this_he,(u8*)unlock_this_th,(u8*)unlock_this_po }};
const ITEM_STRING photo_protecting_string2   = {{(u8*)lock_all_cns,	(u8*)lock_all_cnt, 		(u8*)lock_all_en ,	(u8*)lock_all_ru, 	(u8*)lock_all_ko,	(u8*)lock_all_ja, 	(u8*)lock_all_spa, 	(u8*)lock_all_tu, 	(u8*)lock_all_he, 	(u8*)lock_all_th, 	(u8*)lock_all_po }};
const ITEM_STRING photo_protecting_string3   = {{(u8*)unlock_all_cns,	(u8*)unlock_all_cnt, 	(u8*)unlock_all_en,	(u8*)unlock_all_ru,(u8*)unlock_all_ko,	(u8*)unlock_all_ja,(u8*)unlock_all_spa,(u8*)unlock_all_tu ,(u8*)unlock_all_he ,(u8*)unlock_all_th ,(u8*)unlock_all_po  }};
const ITEM_STRING browse_setting_string0  = {{(u8*)delete_cns, 	(u8*)delete_cnt,	(u8*)delete_en,	(u8*)delete_ru,	(u8*)delete_ko,	(u8*)delete_ja,	(u8*)delete_spa,	(u8*)delete_tu,	(u8*)delete_he,	(u8*)delete_th,	(u8*)delete_po }};
const ITEM_STRING browse_setting_string1  = {{(u8*)lock_cns, 		(u8*)lock_cnt,		(u8*)lock_en ,	(u8*)lock_ru,	(u8*)lock_ko ,	(u8*)lock_ja,	(u8*)lock_spa,	(u8*)lock_tu,	(u8*)lock_he,	(u8*)lock_th,	(u8*)lock_po }};
const ITEM_STRING attribute_string   = {{(u8*)setting_cns,	(u8*)setting_cnt,	(u8*)setting_en ,	(u8*)setting_ru,	(u8*)setting_ko,(u8*)setting_ja,(u8*)setting_spa,(u8*)setting_tu,(u8*)setting_he,(u8*)setting_th,(u8*)setting_po }};
const ITEM_STRING video_string   = {{(u8*)video_cns,	(u8*)video_cnt,	(u8*)video_en, (u8*)video_ru,	(u8*)video_ko,	(u8*)video_ja,	(u8*)video_spa,	(u8*)video_tu,	(u8*)video_he,	(u8*)video_th,	(u8*)video_po}};
const ITEM_STRING photo_string   = {{(u8*)photo_cns,	(u8*)photo_cnt,	(u8*)photo_en ,(u8*)photo_ru,	(u8*)photo_ko ,(u8*)photo_ja,	(u8*)photo_spa,	(u8*)photo_tu,	(u8*)photo_he,	(u8*)photo_th,	(u8*)photo_po }};
const ITEM_STRING browse_string   = {{(u8*)play_cns, 	(u8*)play_cnt,	(u8*)play_en,	(u8*)play_ru,	(u8*)play_ko,	(u8*)play_ja,	(u8*)play_spa,	(u8*)play_tu,	(u8*)play_he,	(u8*)play_th,	(u8*)play_po}};
const ITEM_STRING delete_this_t   = {{(u8*)delete_this_cns,	(u8*)delete_this_cnt,	(u8*)delete_this_en,	(u8*)delete_this_ru,	(u8*)delete_this_ko,	(u8*)delete_this_ja,	(u8*)delete_this_spa,	(u8*)delete_this_tu,	(u8*)delete_this_he,	(u8*)delete_this_th,	(u8*)delete_this_po}};
const ITEM_STRING delete_all_t   = {{(u8*)delete_all_cns, 	(u8*)delete_all_cnt,	(u8*)delete_all_en,	(u8*)delete_all_ru,	(u8*)delete_all_ko,	(u8*)delete_all_ja,	(u8*)delete_all_spa,	(u8*)delete_all_tu,	(u8*)delete_all_he,	(u8*)delete_all_th,	(u8*)delete_all_po}};
const ITEM_STRING lock_this_t   = {{(u8*)lock_this_cns, 		(u8*)lock_this_cnt,	(u8*)lock_this_en	,	(u8*)lock_this_ru,	(u8*)lock_this_ko,	(u8*)lock_this_ja,	(u8*)lock_this_spa,	(u8*)lock_this_tu,	(u8*)lock_this_he,	(u8*)lock_this_th,	(u8*)lock_this_po}};
const ITEM_STRING unlock_this_t   = {{(u8*)unlock_this_cns, (u8*)unlock_this_cnt,	(u8*)unlock_this_en,	(u8*)unlock_this_ru,	(u8*)unlock_this_ko ,(u8*)unlock_this_ja,	(u8*)unlock_this_spa,	(u8*)unlock_this_tu,	(u8*)unlock_this_he,	(u8*)unlock_this_th,	(u8*)unlock_this_po }};
const ITEM_STRING lock_all_t   = {{(u8*)lock_all_cns,      (u8*)lock_all_cnt,		(u8*)lock_all_en , 	(u8*)lock_all_ru,		(u8*)lock_all_ko , (u8*)lock_all_ja,		(u8*)lock_all_spa,		(u8*)lock_all_tu,		(u8*)lock_all_he,		(u8*)lock_all_th,		(u8*)lock_all_po }};
const ITEM_STRING unlock_all_t   = {{(u8*)unlock_all_cns,  (u8*)unlock_all_cnt,	(u8*)unlock_all_en,	(u8*)unlock_all_ru,	(u8*)unlock_all_ko ,(u8*)unlock_all_ja,		(u8*)unlock_all_spa,		(u8*)unlock_all_tu,		(u8*)unlock_all_he,		(u8*)unlock_all_th,		(u8*)unlock_all_po  }};




MENU_ITEM const power_off_item[] = {
		{ 0x12,0,ANL_AUTO_POWER_OFF, 0, (ITEM_STRING *) &power_off_string0,NULL },
		{ 0x12,0,ANL_AUTO_POWER_OFF, 0,(ITEM_STRING *) &power_off_string1, NULL },
		{ 0x12,0,ANL_AUTO_POWER_OFF, 0,(ITEM_STRING *) &power_off_string2, NULL },
		{ 0x90,0x05,0, 0, (ITEM_STRING *) &attribute_page_string2, NULL },
};
MENU_PAGE const power_off_menu = {
		sizeof(power_off_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) power_off_item, (MENU_PAGE *) &attribute_menu,
};


MENU_ITEM const language_item[] = {
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language0, NULL },
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language1, NULL },
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language2, NULL },
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language3, NULL },
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language4, NULL },
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language5, NULL },
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language6, NULL },
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language7, NULL },
#if (MAX_LANGUAGE >=8)
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language8, NULL },
#endif
#if (MAX_LANGUAGE >=9)
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language9, NULL },
#endif
#if (MAX_LANGUAGE >=10)
		{ 0x12,0,ANL_LANGUAGE, 0, (ITEM_STRING *) &language10, NULL },
#endif
		{ 0x90,0x05,0, 0, (ITEM_STRING *) &attribute_page_string1, NULL },
};
MENU_PAGE const language_menu = {
		sizeof(language_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) language_item, (MENU_PAGE *) &attribute_menu,
};


//MENU_ITEM const lingt_source_freq_item[] = {
//		{ 0x12,0, ANL_LIGHT_FREQ, 0, (ITEM_STRING *) &light_source_string0,NULL },
//		{ 0x12,0, ANL_LIGHT_FREQ, 0,(ITEM_STRING *) &light_source_string1, NULL },
//		{ 0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_page_string5, NULL },
//};
//MENU_PAGE const lightsource_menu   = {
//		sizeof(lingt_source_freq_item) / sizeof(MENU_ITEM)-1, 1, 0,
//		(MENU_ITEM *)lingt_source_freq_item, (MENU_PAGE *)&attribute_menu,
//};


MENU_ITEM const screen_save_item[] = {
		{ 0x12,0, ANL_SCREEN_SAVE, 0, (ITEM_STRING *) &sleep_time_string0,NULL },
		{ 0x12,0, ANL_SCREEN_SAVE, 0,(ITEM_STRING *) &sleep_time_string1, NULL },
		{ 0x12,0, ANL_SCREEN_SAVE, 0,(ITEM_STRING *) &sleep_time_string2, NULL },
		{ 0x12,0, ANL_SCREEN_SAVE, 0,(ITEM_STRING *) &sleep_time_string3, NULL },
		{ 0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_page_string3, NULL }
};
MENU_PAGE const  screen_save_menu = {
		sizeof(screen_save_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) screen_save_item, (MENU_PAGE *) &attribute_menu,
};


MENU_ITEM const video_rotate_item[] = {
		{0x12, 0,ANL_VIDEO_ROTATE, 0, (ITEM_STRING *) &off_string, NULL },
		{0x12, 0,ANL_VIDEO_ROTATE, 0, (ITEM_STRING *) &on_string, NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_page_string7, NULL }
};

MENU_PAGE const  video_rotate_menu = {
		sizeof(video_rotate_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) video_rotate_item, (MENU_PAGE *) &attribute_menu,
};

const MENU_ITEM tv_item[]  = {
		{0x12,0, ANL_TV, 0, (ITEM_STRING *) &tv_string0, NULL },
		{0x12,0, ANL_TV, 0, (ITEM_STRING *) &tv_string1, NULL },
		{0x12,0, ANL_TV, 0, (ITEM_STRING *) &tv_string2, NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_tv_mode_string, NULL },
};

const MENU_PAGE tv_menu = {
		sizeof(tv_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) tv_item, (MENU_PAGE *) &attribute_menu, };

MENU_ITEM const beep_sound_item[] = {
		{0x12, 0,ANL_BEEP_SOUND, 0, (ITEM_STRING *) &off_string, NULL },
		{0x12, 0,ANL_BEEP_SOUND, 0, (ITEM_STRING *) &on_string, NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_beep_sound_string, NULL }
};
MENU_PAGE const  beep_sound_menu = {
		sizeof(beep_sound_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) beep_sound_item, (MENU_PAGE *) &attribute_menu,
};


const MENU_ITEM formate_item[] = {
		{0x12,0, ANL_FORMATE, 0, (ITEM_STRING *) &formate_string0, NULL },
		{0x12,0, ANL_FORMATE, 0, (ITEM_STRING *) &formate_string1, NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_page_string0, NULL }
};
const MENU_PAGE formate_menu = {
		sizeof(formate_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) formate_item, (MENU_PAGE *) &attribute_menu, };

const MENU_ITEM default_item[]  = {
		{0x12,0, ANL_DEFAULT, 0, (ITEM_STRING *) &default_string0, NULL },
		{0x12,0, ANL_DEFAULT, 0, (ITEM_STRING *) &default_string1, NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_page_string4, NULL }
};
const MENU_PAGE default_menu = {
		sizeof(default_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) default_item, (MENU_PAGE *) &attribute_menu, };

const MENU_ITEM video_night_light_item[] = {
		{ 0x12,0, ANL_NIGHT_LIGHT, 0, (ITEM_STRING *) &off_string, NULL },
		{ 0x12,0, ANL_NIGHT_LIGHT, 0, (ITEM_STRING *) &on_string, NULL },
		{ 0x90,0x05, 0, 0, (ITEM_STRING *) &attribute_page_string9,NULL },
};
const MENU_PAGE video_night_light_menu = {
		sizeof(video_night_light_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) video_night_light_item, (MENU_PAGE *) &video_menu,
};

const MENU_ITEM version_item[] = {
		{0x12,0, ANL_VERSION, 0, (ITEM_STRING *) &version_string0, NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &attribute_page_string8, NULL }
};

const MENU_PAGE version_menu = {
		sizeof(version_item) / sizeof(MENU_ITEM)-1, 1,0,
		(MENU_ITEM *) version_item, (MENU_PAGE *) &attribute_menu, };

const MENU_ITEM ATTRIBUTE_SETTING_ITEM[] = {
		{ 0x30,0, 0,RES_ATRRIBUTE_1FORMATE_BMP,(ITEM_STRING *) &attribute_page_string0,(MENU_PAGE *) &formate_menu },
		{ 0x30,0, 0,RES_ATRRIBUTE_2LANGUAGE_BMP,(ITEM_STRING *) &attribute_page_string1,(MENU_PAGE *) &language_menu },
		{ 0x30,0, 0, RES_ATRRIBUTE_3AUTO_POWEROFF_BMP,(ITEM_STRING *) &attribute_page_string2,(MENU_PAGE *) &power_off_menu },
		{ 0x30,0, 0,RES_ATRRIBUTE_4SCREEN_SAVE_BMP,(ITEM_STRING *) &attribute_page_string3,(MENU_PAGE *) &screen_save_menu },
		{ 0x30,0, 0,RES_ATRRIBUTE_5DEFAULT_BMP,(ITEM_STRING *) &attribute_page_string4,(MENU_PAGE *) &default_menu },	
		{ 0x32,0, ANL_DATE_AJUST, RES_ATRRIBUTE_7DATE_BMP,(ITEM_STRING *) &attribute_page_string6, NULL },
		{ 0x30,0, 0,RES_ATRRIBUTE_8VIDEO_ROTATE_BMP,(ITEM_STRING *) &attribute_page_string7,(MENU_PAGE *) &video_rotate_menu },
		{ 0x30,0, 0,RES_ATRRIBUTE_9NIGHT_VISION_BMP,(ITEM_STRING *) &attribute_page_string9,(MENU_PAGE *) &video_night_light_menu },
		#if (1 == DEFAULT_TVOUT_EN)
		{ 0x30,0, 0,RES_ATRRIBUTE_ATV_BMP,(ITEM_STRING *) &attribute_tv_mode_string,(MENU_PAGE *) &tv_menu },
		#endif
		{ 0x30,0, 0,RES_ATRRIBUTE_BVER_BMP,(ITEM_STRING *) &attribute_page_string8,(MENU_PAGE *) &version_menu },
		{ 0xF0,0x05, OSD_MENU_ATTRIBUTE,RES_ATRRIBUTE_CSETTING_BMP, (ITEM_STRING *) &attribute_string,NULL }
};
const MENU_PAGE attribute_menu = {
		sizeof(ATTRIBUTE_SETTING_ITEM) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) ATTRIBUTE_SETTING_ITEM, NULL, };

const MENU_ITEM VIDEO_RESOLUTION_SETTING_ITEM[] = {
		{ 0x12,0, ANL_VIDEO_MP, 0, (ITEM_STRING *) &video_resolution_string2,NULL },		// 1
		//{ 0x12,0, ANL_VIDEO_MP, 0, (ITEM_STRING *) &video_resolution_string0,NULL },
		{ 0x12,0, ANL_VIDEO_MP, 0, (ITEM_STRING *) &video_resolution_string3, NULL },      // 3
		{ 0x12,0, ANL_VIDEO_MP, 0, (ITEM_STRING *) &video_resolution_string1,NULL },		// 2
		{ 0x90,0x05, 0, 0, (ITEM_STRING *) &video_setting_string0,NULL },
};
const MENU_PAGE video_resolution_menu = {
		sizeof(VIDEO_RESOLUTION_SETTING_ITEM) / sizeof(MENU_ITEM)-1, 1, 0,
				(MENU_ITEM *) VIDEO_RESOLUTION_SETTING_ITEM,
				(MENU_PAGE *) &video_menu, };

const MENU_ITEM VIDEO_LOOP_SETTING_ITEM[] = {
		{ 0x12,0, ANL_LOOP_VIDEO, 0, (ITEM_STRING *) &video_loop_string0,NULL },
		{ 0x12,0, ANL_LOOP_VIDEO, 0, (ITEM_STRING *) &video_loop_string1, NULL },
		{ 0x12,0, ANL_LOOP_VIDEO, 0, (ITEM_STRING *) &video_loop_string2, NULL },
		{ 0x12,0, ANL_LOOP_VIDEO, 0, (ITEM_STRING *) &video_loop_string3,NULL },
		{ 0x90,0x05, 0, 0, (ITEM_STRING *) &video_setting_string3,NULL },
};
const MENU_PAGE video_loop_menu = {
		sizeof(VIDEO_LOOP_SETTING_ITEM) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) VIDEO_LOOP_SETTING_ITEM, (MENU_PAGE *) &video_menu, };

const MENU_ITEM MOTION_DECTECTION_ITEM[] = {
		{ 0x12,0, ANL_MOTION_DECTECTION, 0, (ITEM_STRING *) &video_detecting_string0,NULL },
		{ 0x12,0, ANL_MOTION_DECTECTION, 0,(ITEM_STRING *) &video_detecting_string1, NULL },
		{ 0x90,0x05, 0, 0, (ITEM_STRING *) &video_setting_string2,NULL },
};
const MENU_PAGE motion_detection_menu = {
		sizeof(MOTION_DECTECTION_ITEM) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) MOTION_DECTECTION_ITEM, (MENU_PAGE *) &video_menu, };

const MENU_ITEM VIDEO_VOICE_SETTING_ITEM[] = {
		{0x12,0, ANL_VIDEO_VOICE, 0,(ITEM_STRING *) &video_detecting_string0, NULL },
		{0x12,0,ANL_VIDEO_VOICE, 0, (ITEM_STRING *) &video_detecting_string1,NULL },
		{0x90,0x05, 0, 0, (ITEM_STRING *) &video_setting_string4,NULL },
};
const MENU_PAGE video_vioce_menu = {
		sizeof(VIDEO_VOICE_SETTING_ITEM) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) VIDEO_VOICE_SETTING_ITEM, (MENU_PAGE *) &video_menu,
};

const MENU_ITEM video_date_tag_item[] = {
		{ 0x12,0, ANL_VIDEO_DATE_TAG, 0, (ITEM_STRING *) &video_date_string0, NULL },
		{ 0x12,0, ANL_VIDEO_DATE_TAG, 0, (ITEM_STRING *) &video_date_string1, NULL },
		{ 0x90,0x05, 0, 0, (ITEM_STRING *) &video_setting_string1,NULL },
};
const MENU_PAGE video_date_menu = {
		sizeof(video_date_tag_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) video_date_tag_item, (MENU_PAGE *) &video_menu,
};


const MENU_ITEM video_g_sensor_item[] = {
		{ 0x12,0, ANL_GSENSOR_SENS, 0, (ITEM_STRING *) &video_gsensor_string0, NULL },
		{ 0x12,0, ANL_GSENSOR_SENS, 0, (ITEM_STRING *) &video_gsensor_string1, NULL },
		{ 0x12,0, ANL_GSENSOR_SENS, 0, (ITEM_STRING *) &video_gsensor_string2, NULL },
		{ 0x12,0, ANL_GSENSOR_SENS, 0, (ITEM_STRING *) &video_gsensor_string3, NULL },
		{ 0x90,0x05, 0, 0, (ITEM_STRING *) &video_setting_string6,NULL },
};
const MENU_PAGE video_g_sensor_menu = {
		sizeof(video_g_sensor_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) video_g_sensor_item, (MENU_PAGE *) &video_menu,
};

const MENU_ITEM VIDEO_SETTING_ITEM[] = {
		{ 0x30,0, 0,RES_VIDEO_1MP_BMP, (ITEM_STRING *) &video_setting_string0,(MENU_PAGE *) &video_resolution_menu },
		{ 0x30,0, 0,RES_VIDEO_2DATE_TAG_BMP,(ITEM_STRING *) &video_setting_string1,(MENU_PAGE *) &video_date_menu },
		{ 0x30,0, 0,RES_VIDEO_3MOTION_DECTION_BMP,(ITEM_STRING *) &video_setting_string2,(MENU_PAGE *) &motion_detection_menu },
		{ 0x30,0, 0,RES_VIDEO_4LOOP_BMP, (ITEM_STRING *) &video_setting_string3,(MENU_PAGE *) &video_loop_menu },
		{ 0x30,0, 0,RES_VIDEO_5VOICE_BMP, (ITEM_STRING *) &video_setting_string4,(MENU_PAGE *) &video_vioce_menu },
		#if (G_SEN_USE != G_SEN_NULL)
		{ 0x30,0, 0,RES_VIDEO_6G_SENSOR_BMP,(ITEM_STRING *) &video_setting_string6,(MENU_PAGE *) &video_g_sensor_menu },
		#endif
		{ 0xF0,0x05, OSD_MENU_VIDEO,RES_VIDEO_7VIDEO_BMP, (ITEM_STRING *) &video_string,(MENU_PAGE *) &attribute_menu },
};
const MENU_PAGE video_menu = {
		sizeof(VIDEO_SETTING_ITEM) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) VIDEO_SETTING_ITEM, NULL, };

const MENU_ITEM photo_mp_item[]  = {
		{ 0x12,0, ANL_PHOTO_MP, 0, (ITEM_STRING *) &photo_resolution_string3,NULL },// 1
		{ 0x12,0, ANL_PHOTO_MP, 0,(ITEM_STRING *) &photo_resolution_string2, NULL },// 0
		{ 0x12,0, ANL_PHOTO_MP, 0,(ITEM_STRING *) &photo_resolution_string0, NULL },// 2
		{ 0x12,0, ANL_PHOTO_MP, 0,(ITEM_STRING *) &photo_resolution_string1, NULL },// 3
		{ 0x90,0x05, 0, 0,(ITEM_STRING *) &photo_setting_string0, NULL },
};
const MENU_PAGE photo_mp_menu = {
		sizeof(photo_mp_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) photo_mp_item, (MENU_PAGE *) &photo_menu,
};

const MENU_ITEM PHOTO_VIEW_ITEM[] = {
		{0x12,0, ANL_FAST_VIEW, 0, (ITEM_STRING *) &photo_view_string0, NULL },
		{0x12,0, ANL_FAST_VIEW, 0, (ITEM_STRING *) &photo_view_string1, NULL },
		{0x12,0, ANL_FAST_VIEW, 0, (ITEM_STRING *) &photo_view_string2, NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &photo_setting_string1, NULL },
};
const MENU_PAGE photo_slide_menu = {
		sizeof(PHOTO_VIEW_ITEM) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) PHOTO_VIEW_ITEM, (MENU_PAGE *) &photo_menu, };

const MENU_ITEM PHOTO_DATE_SETTING_ITEM[] = {
		{0x12,0, ANL_PHOTO_DATE_TAG, 0,(ITEM_STRING *) &photo_date_string0, NULL },
		{0x12,0, ANL_PHOTO_DATE_TAG, 0, (ITEM_STRING *) &photo_date_string1,NULL },
		{0x90,0x05, 0, 0,(ITEM_STRING *) &photo_setting_string2, NULL },
};
const MENU_PAGE photo_date_menu = {
		sizeof(PHOTO_DATE_SETTING_ITEM) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) PHOTO_DATE_SETTING_ITEM, (MENU_PAGE *) &photo_menu, };

const MENU_ITEM photo_setting_item[] = {
		{ 0x30,0, 0,RES_PHOTO_1MP_BMP, (ITEM_STRING *) &photo_setting_string0,(MENU_PAGE *) &photo_mp_menu },
		{ 0x30,0, 0,RES_PHOTO_2FAST_VIEW_BMP,(ITEM_STRING *) &photo_setting_string1,(MENU_PAGE *) &photo_slide_menu },
		{ 0x30,0, 0,RES_PHOTO_3DTAE_TAG_BMP,(ITEM_STRING *) &photo_setting_string2,(MENU_PAGE *) &photo_date_menu },
		{ 0xF0,0x05, OSD_MENU_PHOTO,RES_PHOTO_4PHOTO_BMP, (ITEM_STRING *) &photo_string,(MENU_PAGE *) &attribute_menu },
};
const MENU_PAGE photo_menu = {
		sizeof(photo_setting_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) photo_setting_item, (MENU_PAGE *) &photo_menu, };

const MENU_ITEM browse_delete_this_item[] = {
		{0x12,0, ANL_BROWSE_DELETE_THIS, 0,(ITEM_STRING *) &cancel_string, NULL },
		{0x12,0, ANL_BROWSE_DELETE_THIS, 0, (ITEM_STRING *) &ok_string, NULL },
		{0x90,0x01, 0, 0, (ITEM_STRING *) &delete_this_t, NULL }
};
const MENU_PAGE browse_delete_this_menu = {
		sizeof(browse_delete_this_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) browse_delete_this_item, (MENU_PAGE *) &browse_menu, };

const MENU_ITEM browse_delete_all_item[] = {
		{0x12,0, ANL_BROWSE_DELETE_ALL, 0, (ITEM_STRING *) &cancel_string, NULL },
		{0x12,0, ANL_BROWSE_DELETE_ALL, 0, (ITEM_STRING *) &ok_string, NULL },
		{0x90,0x01, 0, 0, (ITEM_STRING *) &delete_all_t, NULL },
};
const MENU_PAGE photo_delete_all_menu = {
		sizeof(browse_delete_all_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) browse_delete_all_item, (MENU_PAGE *) &browse_menu, };

const MENU_ITEM browse_delete_item[]  = {
		{ 0x10,0, 0, 0, (ITEM_STRING *) &photo_deleting_string0,(MENU_PAGE *) &browse_delete_this_menu },
		{ 0x10,0, 0, 0,(ITEM_STRING *) &photo_deleting_string1,(MENU_PAGE *) &photo_delete_all_menu },
		{ 0x90,0x05, 0, 0,(ITEM_STRING *) &browse_setting_string0,NULL},
};

const MENU_PAGE browse_delete_menu = {
		sizeof(browse_delete_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) browse_delete_item, (MENU_PAGE *) &browse_menu, };

const MENU_ITEM browse_lock_this_item[] = {
		{0x12,0,ANL_BROWSE_LOCK_THIS, 0, (ITEM_STRING *) &cancel_string, NULL },
		{0x12,0,ANL_BROWSE_LOCK_THIS, 0, (ITEM_STRING *) &ok_string, NULL },
		{0x90,0x01,0, 0, (ITEM_STRING *) &lock_this_t, NULL },
};
const MENU_PAGE browse_lock_this_menu = {
		sizeof(browse_lock_this_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) browse_lock_this_item, (MENU_PAGE *) &browse_menu, };

const MENU_ITEM browse_unlock_this_item[] = {
		{0x12,0,ANL_BROWSE_UNLOCK_THIS, 0,(ITEM_STRING *) &cancel_string, NULL },
		{0x12,0,ANL_BROWSE_UNLOCK_THIS, 0, (ITEM_STRING *) &ok_string, NULL },
		{0x90,0x01,0, 0, (ITEM_STRING *) &unlock_this_t, NULL },
};
const MENU_PAGE browse_unlock_this_menu = {
		sizeof(browse_unlock_this_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) browse_unlock_this_item, (MENU_PAGE *) &browse_menu, };
const MENU_ITEM browse_lock_all_item[] = {
		{0x12,0,ANL_BROWSE_LOCK_ALL, 0, (ITEM_STRING *) &cancel_string, NULL },
		{0x12,0,ANL_BROWSE_LOCK_ALL, 0, (ITEM_STRING *) &ok_string, NULL },
		{0x90,0x01,0, 0, (ITEM_STRING *) &lock_all_t, NULL }
};
const MENU_PAGE browse_lock_all_menu = {
		sizeof(browse_lock_all_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) browse_lock_all_item,
		(MENU_PAGE *) &browse_menu,
};
const MENU_ITEM browse_unlock_all_item[] = {
		{0x12,0, ANL_BROWSE_UNLOCK_ALL, 0, (ITEM_STRING *) &cancel_string, NULL },
		{0x12,0, ANL_BROWSE_UNLOCK_ALL, 0, (ITEM_STRING *) &ok_string, NULL },
		{0x90,0x01, 0, 0, (ITEM_STRING *) &unlock_all_t, NULL },
};
const MENU_PAGE browse_unlock_all_menu = {
		sizeof(browse_unlock_all_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) browse_unlock_all_item,
		(MENU_PAGE *) &browse_menu, };

const MENU_ITEM browse_protect_item[] = {
		{ 0x10,0, 0, 0, (ITEM_STRING *) &photo_protecting_string0,(MENU_PAGE *) &browse_lock_this_menu },
		{ 0x10,0, 0, 0,(ITEM_STRING *) &photo_protecting_string1,(MENU_PAGE *) &browse_unlock_this_menu },
		{ 0x10,0, 0, 0,(ITEM_STRING *) &photo_protecting_string2,(MENU_PAGE *) &browse_lock_all_menu },
		{ 0x10,0, 0, 0,(ITEM_STRING *) &photo_protecting_string3,(MENU_PAGE *) &browse_unlock_all_menu },
		{ 0x90,0x05, 0, 0,(ITEM_STRING *) &browse_setting_string1,NULL },
};
const MENU_PAGE browse_protect_menu = {
		sizeof(browse_protect_item) / sizeof(MENU_ITEM)-1, 1, 0,
		(MENU_ITEM *) browse_protect_item,
		(MENU_PAGE *) &browse_menu, };

const MENU_ITEM browse_menu_item[] = {
		{0x30,0, 0, RES_BROWSE_1DELETE_BMP,(ITEM_STRING *) &browse_setting_string0,(MENU_PAGE *) &browse_delete_menu },
		{0x30,0, 0,RES_BROWSE_2PROTECT_BMP, (ITEM_STRING *) &browse_setting_string1,(MENU_PAGE *) &browse_protect_menu },
		{0xF0,0x05, OSD_MENU_BROWSE,RES_BROWSE_3PLAYBACK_BMP, (ITEM_STRING *) &browse_string,(MENU_PAGE *) &attribute_menu },
};
const MENU_PAGE browse_menu = {
		sizeof(browse_menu_item) / sizeof(MENU_ITEM) - 1, 1, 0,
		(MENU_ITEM *) browse_menu_item, NULL, };

const ACT_LIST act_list[] = {
		{ANL_VIDEO_MP, &user_set_jpeg_video_size},
		{ANL_LOOP_VIDEO, &user_set_crc_record},
		{ANL_MOTION_DECTECTION, &user_set_moving_detect},
		{ANL_VIDEO_VOICE, &user_set_record_mute},
		{ANL_VIDEO_DATE_TAG, &user_set_video_time_info},
		{ANL_NIGHT_LIGHT, &user_set_night_light},
		{ANL_GSENSOR_SENS, &user_set_Gsensor_senstivity},
		{ANL_PHOTO_MP, &user_set_jpeg_picture_size},
		{ANL_FAST_VIEW, &user_set_fast_view},
		{ANL_PHOTO_DATE_TAG, &user_set_picture_time_info},
		{ANL_AUTO_POWER_OFF, (user_set)user_set_poweroff},
		{ANL_LANGUAGE, (user_set)user_set_language},
		{ANL_SCREEN_SAVE, &user_set_backlight},
		{ANL_VIDEO_ROTATE, &user_set_video_rotate},
		{ANL_TV,(user_set)(&user_set_tv_mode)},
		{ANL_BEEP_SOUND, &user_set_beep_sound},
		{ANL_FORMATE, (user_set)(&user_set_format)/*&user_set_format*/},
		{ANL_DEFAULT, (user_set)(&spi_param_factory)},
		{ANL_BROWSE_DELETE_THIS, (user_set)(&user_set_delete_current)/*&user_set_delete_current*/},
		{ANL_BROWSE_DELETE_ALL, (user_set)(&user_set_delete_all)/*&user_set_delete_all*/},
		{ANL_BROWSE_LOCK_THIS, (user_set)(&user_set_lock_current)/*&user_set_lock_current*/},
		{ANL_BROWSE_UNLOCK_THIS, (user_set)(&user_set_unlock_current)/*&user_set_unlock_current*/},
		{ANL_BROWSE_LOCK_ALL, (user_set)(&user_set_lock_all)/*&user_set_lock_all*/},
		{ANL_BROWSE_UNLOCK_ALL, (user_set)(&user_set_unlock_all)/*&user_set_unlock_all*/},
		{ANL_DATE_AJUST, (user_set)(&date_adjust_setting)},
		{ANL_VERSION, NULL}
};

const MENU_LIST menu_list[]  = {
		{MENU_IDLE, MENU_IDLE },
		{MENU_VIDEO, MENU_ATTRIBUTE},
		{MENU_PHOTO, MENU_ATTRIBUTE},
		{MENU_BROWSE, MENU_ATTRIBUTE},
		{MENU_ATTRIBUTE, MENU_IDLE}
};

const MENU_TO_PAGE menu2page[] = {

		{MENU_IDLE,  NULL },
		{MENU_VIDEO, (MENU_PAGE *)&video_menu},
		{MENU_PHOTO, (MENU_PAGE *)&photo_menu},
		{MENU_BROWSE, (MENU_PAGE *)&browse_menu},
		{MENU_ATTRIBUTE, (MENU_PAGE *)&attribute_menu},
};

//每一级除了标题跟底部的信息之外，开的窗口的大小
const MENU_BACKGROUND_HIGHLIGHT menu_level_region[] = {
		{  OSD_MENU_Menu1B1,ALPHA_0X80_COLOR, MENU_LEVEL1_REGION_X, MENU_LEVEL1_REGION_Y, MENU_LEVEL1_REGION_W,	MENU_LEVEL1_REGION_H },
		{  OSD_MENU_Menu2B ,ALPHA_0X00_COLOR, MENU_LEVEL2_REGION_X, MENU_LEVEL2_REGION_Y, MENU_LEVEL2_REGION_W,  MENU_LEVEL2_REGION_H },
		{  OSD_MENU_Menu2B ,ALPHA_0X00_COLOR, MENU_LEVEL3_REGION_X, MENU_LEVEL3_REGION_Y, MENU_LEVEL3_REGION_W,  MENU_LEVEL3_REGION_H }
};

//每一级菜单项 当前选中的菜单项，需要高亮显示的区域
const MENU_BACKGROUND_HIGHLIGHT menu_highlight[] = {
		{ OSD_MENU_MenuItem1S, ALPHA_0X80_COLOR, MENU_LEVEL1_HIGHLIGHT_START_X, MENU_LEVEL1_HIGHLIGHT_START_Y, MENU_LEVEL1_HIGHLIGHT_W, MENU_LEVEL1_HIGHLIGHT_H },
		{ OSD_MENU_MenuItem2S ,ALPHA_0X00_COLOR, MENU_LEVEL2_HIGHLIGHT_START_X, MENU_LEVEL2_HIGHLIGHT_START_Y, MENU_LEVEL2_HIGHLIGHT_W, MENU_LEVEL2_HIGHLIGHT_H },
		{ OSD_MENU_MenuItem2S ,ALPHA_0X00_COLOR, MENU_LEVEL3_HIGHLIGHT_START_X, MENU_LEVEL3_HIGHLIGHT_START_Y, MENU_LEVEL3_HIGHLIGHT_W, MENU_LEVEL3_HIGHLIGHT_H }
};

//每一级菜单项需要更新的时候，要清除的区域
const MENU_BACKGROUND_HIGHLIGHT menu_level_clear_region[] = {
		{  OSD_MENU_Menu1B1,ALPHA_0X80_COLOR, MENU_LEVEL1_REGION_X, MENU_LEVEL1_REGION_Y, MENU_LEVEL1_REGION_W,	MENU_LEVEL1_REGION_H },
		{  OSD_MENU_Menu2B ,ALPHA_0X00_COLOR, MENU_LEVEL2_REGION_X+2, MENU_LEVEL2_REGION_Y+2, MENU_LEVEL2_REGION_W-4,  MENU_LEVEL2_REGION_H-4 },  //外围有方框，去除方框的区域
		{  OSD_MENU_Menu2B ,ALPHA_0X00_COLOR, MENU_LEVEL3_REGION_X+2, MENU_LEVEL3_REGION_Y+2, MENU_LEVEL3_REGION_W-4,  MENU_LEVEL3_REGION_H-4 }  //外围有方框，去除方框的区域
};

