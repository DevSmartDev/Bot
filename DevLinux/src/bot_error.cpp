#include "bot_error.h"
#ifndef __bot_CHART__
#include "bot_login.h"
#endif

std::map<gint, const gchar *> MessageResultMap;

static void bot_error_init_maptable(void);
static void bot_error_init_widgets(void);




void bot_error_finalize(void)
{
}


gboolean bot_error_init(void)
{
    bot_error_init_maptable();
    bot_error_init_widgets();

//    std::cout << "elements in mymap:" << '\n';
//    std::cout << "1 => " << MessageResultMap.find((gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR)->second << '\n';
    return TRUE;
}
static void bot_error_init_widgets(void)
{
}



static void bot_error_init_maptable(void)
{
    MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NON_USCOREERR]                                                     ="No Error";
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__MYSQL_USCOREERR]                                                   =("Server truy cập vào cơ sở dữ liệu bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__USER_USCOREPASS_USCOREERR]                                         =("Tên tài khoản hoặc mật khẩu bị sai"); // chua sd
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__INVALID_USCORELOGIN_USCOREERR]                                     =("Tài khoản của bạn bị timeout");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__INTERNAL_USCOREERR]                                                =("Lỗi internal");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__UNKNOW_USCOREERR]                                                  =("Lỗi unknow");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__TIMEOUT_USCOREERR]                                                 =("Server truyền dữ liệu đến trạm bị timout");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__OFFLINE_USCOREERR]                                                 =("Trạm này chưa kết nối với Server");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__MODE_USCOREERR]                                                    =("Mất đồng bộ chế độ giữa cơ sở dữ liệu và trạm");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__LIGHTNUM_USCOREERR]                                                =("Mất đồng bộ số lượng đèn giữa cơ sở dữ liệu và trạm");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__LINENUM_USCOREERR]                                                 =("Mất đồng bộ số lượng đèn giữa cơ sở dữ liệu và trạm");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__CLOCK_USCOREERR]                                                   =("Đồng hồ thời gian thực của trạm bị hư");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__EXIST_USCOREDCU_USCOREERR]                                         =("Tồn tại trạm này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NOEXIST_USCOREDCU_USCOREERR]                                       =("Không tồn tại trạm này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__EXIST_USCORELCU_USCOREERR]                                         =("Tồn tại đèn này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NOEXIST_USCORELCU_USCOREERR]                                       =("Không tồn tại đèn này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__MEM_USCOREERR]                                                     =("Bộ nhớ của trạm bị hư");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__GET_USCOREPRO_USCOREFROM_USCOREDB_USCOREERR]                       =("Lỗi lấy chương trình từ cơ sở dữ liệu"); // chua sd
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__USER_USCOREPASSWD_USCOREERR]                                       =("Tên tài khoản hoặc mật khẩu bị sai");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__ADD_USCORELCU_USCOREERR]                                           =("Thêm đèn đến trạm để trạm này quản lý bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__REMOVE_USCORELCU_USCOREERR]                                        =("Xoá đèn trên trạm bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__LIMIT_USCORELCU_USCOREERR]                                         =("Không thể thêm đèn đến trạm vì số lượng đèn trên trạm này đã đạt giới hạn");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__SET_USCORESCHEDULE_USCORELCU_USCOREERR]                            =("Thiết lập lập lịch cho trạm bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__GET_USCORESCHEDULE_USCORELCU_USCOREERR]                            =("Lấy lập lịch trên trạm bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__VERIFY_USCORESCHEDULE_USCORELCU_USCOREERR]                         =("Kiểm tra lập lich trên trạm bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__GET_USCORELCU_USCOREERR]                                           =("Lấy thông tin đèn bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__ADD_USCORELINE_USCOREERR]                                          =("Thêm cổng điều khiền đèn đến trạm để trạm này quản lý bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__REMOVE_USCORELINE_USCOREERR]                                       =("Xoá cổng điều khiền đèn trên trạm bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__LIMIT_USCORELINE_USCOREERR]                                        =("Không thể thêm cổng điều khiền đèn đến trạm vì số lượng cổng điều khiền đèn trên trạm này đã đạt giới hạn");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__SET_USCORESCHEDULE_USCORELINE_USCOREERR]                           =("Thiết lập lập lịch cho trạm bị lỗi");// chua sd
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__GET_USCORESCHEDULE_USCORELINE_USCOREERR]                           =("Lấy lập lịch trên trạm bị lỗi");// chua sd
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__VERIFY_USCORESCHEDULE_USCORELINE_USCOREERR]                        =("Kiểm tra lập lich trên trạm bị lỗi");// chua sd
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__GET_USCORELINE_USCOREERR]                                          =("Lấy thông tin cổng điều khiền đèn bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__EXIST_USCOREPROGRAM_USCOREERR]                                     =("Tồn tại tên chương trình này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NOEXIST_USCOREPROGRAM_USCOREERR]                                   =("Không tồn tại tên chương trình này trong cơ sở dữ liệu");

	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__ISUSE_USCOREPROGRAM_USCOREERR]                                     =("Chương trình này đã được dùng cho trạm khác");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__MANAGE_USCOREDCU_USCOREPRIVILEGE_USCOREERR]                        =("Tài khoản này không có phần quyền quản lý trạm");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__MANAGE_USCORELINE_USCORELCU_USCOREPRIVILEGE_USCOREERR]             =("Tài khoản này không có phần quyền quản lý đèn");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__CONTROL_USCORELINE_USCORELCU_USCOREPRIVILEGE_USCOREERR]            =("Tài khoản này không có phần quyền điều khiển đèn");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__SETUP_USCOREDEVICE_USCOREPRIVILEGE_USCOREERR]                      =("Tài khoản này không có phần quyền lấp đặt thiết bị");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__PROGRAM_USCOREPRIVILEGE_USCOREERR]                                 =("Tài khoản này không có phần quyền quản lý trạm");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__ADMINISTRATOR_USCOREPRIVILEGE_USCOREERR]                           =("Tài khoản này không có phần quyền admin");

	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__EXIST_USCOREUSER_USCOREERR]                                        =("Tồn tại tên tài khoản này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NOEXIST_USCOREUSER_USCOREERR]                                      =("Không tồn tại tên tài khoảng này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__INVALID_USCOREMONTH_USCOREDAYSCHEDULE_USCOREERR]                   =("Trường tháng trong lập lich tháng không hợp lệ");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__EXIST_USCOREDAYSCHEDULE_USCOREERR]                                 =("Tồn tại tên lập lich tháng này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NOEXIST_USCOREDAYSCHEDULE_USCOREERR]                               =("Không tồn tại tên lập lich tháng này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__EXIST_USCORESCHEDULE_USCOREERR]                                    =("Tồn tại tên lập lich này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__NOEXIST_USCORESCHEDULE_USCOREERR]                                  =("Không tồn tại tên lập lich này trong cơ sở dữ liệu");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__CONTROL_USCORELCU_USCOREERR]                                       =("Server điều khiển đèn bị lỗi");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__OTHER_USCOREUSER_USCORECONTROL_USCORETEMP_USCORELCU_USCOREERR]     =("Không thể điền khiển tạm thời đèn vì đã có một tài khoản khác đang điền khiển tạm thời đèn này");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__LOGIN_USCOREWITH_USCOREOTHER_USCOREDEV_USCOREERR]                  =("Tài khoản này đã được đăng nhập từ nơi khác.");
	MessageResultMap[(gint)ns1__MESSAGE_USCORERESULT_USCOREEnum__DCU_USCOREBUSY_USCOREERR]                                          =("Trạm điều khiển đang bận.");

}

gboolean bot_error_check_message_result(GtkWidget *parentWidget, gchar* msg, gint result_code)
{
    gchar *notifice_content = NULL;
    if (result_code < 0)
    {
        notifice_content = g_strdup("Không kết nối được với Server");
    }
    else
    if(result_code == LOGOUT_TIMOUT_ERROR ||
       result_code == LOGOUT_OTHER_ERROR)
    {
        notifice_content = g_strdup((gchar *)MessageResultMap.find(result_code)->second);
    }
    else
    {
        notifice_content = g_strconcat(msg, (gchar *)MessageResultMap.find(result_code)->second, NULL);

    }

#ifndef __bot_CHART__
    if(result_code == LOGOUT_TIMOUT_ERROR ||
       result_code == LOGOUT_OTHER_ERROR || result_code<0)
    {
        DEBUG("============== result_code: %d\n", result_code);
        bot_user_logout();
    }
#endif

    /* Show error popup here */
    bot_error_notifice_run(parentWidget, notifice_content);

    if (notifice_content)
        g_free(notifice_content);

#ifndef __bot_CHART__
     if(result_code == LOGOUT_TIMOUT_ERROR ||
       result_code == LOGOUT_OTHER_ERROR|| result_code<0)
    {
        bot_login();
    }
#endif
    return TRUE;
}

gboolean bot_error_notifice_run(GtkWidget *parentWidget, gchar *notifice_content)
{
    bot_utils_message_box(GTK_WINDOW(parentWidget), GTK_MESSAGE_WARNING,
                          GTK_BUTTONS_OK, notifice_content);
}
