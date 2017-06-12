static const gchar *smartstreetlight_gui = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<!-- Generated with glade 3.18.3 -->\
<interface>\
  <requires lib=\"gtk+\" version=\"3.10\"/>\
  <object class=\"GtkDialog\" id=\"add_dcu_dialog\">\
    <property name=\"width_request\">450</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"margin_bottom\">5</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"window_position\">center-always</property>\
    <property name=\"default_width\">450</property>\
    <property name=\"default_height\">400</property>\
    <property name=\"type_hint\">dialog</property>\
    <property name=\"deletable\">False</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox27\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area27\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"dcu_add_ok\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"dcu_add_cancel\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkLabel\" id=\"lb_dialog_name\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_left\">5</property>\
            <property name=\"margin_right\">5</property>\
            <property name=\"margin_top\">5</property>\
            <property name=\"margin_bottom\">5</property>\
            <property name=\"label\" translatable=\"yes\">ĐĂNG KÝ TRẠM MỚI</property>\
            <property name=\"angle\">0.11</property>\
            <attributes>\
              <attribute name=\"font-desc\" value=\"Bitstream Vera Serif 16\"/>\
              <attribute name=\"weight\" value=\"bold\"/>\
              <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
            </attributes>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box13\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"border_width\">5</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkGrid\" id=\"grid5\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"row_spacing\">10</property>\
                <property name=\"column_spacing\">10</property>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_dcu_entry_id\">\
                    <property name=\"width_request\">300</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_dcu_entry_phone\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_dcu_entry_address\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_dcu_entry_gps\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">4</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label97\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Mã trạm:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label98\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Số điện thoại:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label102\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Địa chỉ:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label103\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Tọa độ:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">4</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"add_dcu_combobox_mode\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <items>\
                      <item translatable=\"yes\">&lt;none&gt;</item>\
                      <item translatable=\"yes\">Wireless Mode</item>\
                      <item translatable=\"yes\">Line Mode</item>\
                    </items>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">6</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label104\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Chế độ HĐ:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">6</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label108\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Ghi chú:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">7</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_dcu_entry_note\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">7</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label109\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Khu vực:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">5</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"add_dcu_combobox_zone\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">5</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"add_dcu_label_error\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"xalign\">0</property>\
                <attributes>\
                  <attribute name=\"foreground\" value=\"#efef29292929\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-3\">dcu_add_ok</action-widget>\
      <action-widget response=\"-7\">dcu_add_cancel</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"add_lcu_dialog\">\
    <property name=\"width_request\">450</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"margin_bottom\">5</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"window_position\">center-always</property>\
    <property name=\"default_width\">450</property>\
    <property name=\"default_height\">400</property>\
    <property name=\"type_hint\">normal</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox29\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area29\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_add_ok\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"dcu_add_cancel4\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkLabel\" id=\"lb_dialog_lcu_name\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_bottom\">20</property>\
            <property name=\"label\" translatable=\"yes\">ĐĂNG KÝ MỚI\
THIẾT BỊ ĐIỀU KHIỂN ĐÈN</property>\
            <property name=\"justify\">center</property>\
            <property name=\"ellipsize\">middle</property>\
            <property name=\"angle\">0.10000000000000001</property>\
            <attributes>\
              <attribute name=\"font-desc\" value=\"Bitstream Vera Serif 16\"/>\
              <attribute name=\"weight\" value=\"bold\"/>\
              <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
            </attributes>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box27\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"border_width\">5</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkGrid\" id=\"grid8\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"row_spacing\">10</property>\
                <property name=\"column_spacing\">10</property>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label111\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Tọa độ (GPS):</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_lcu_entry_gps\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label110\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Loại đèn:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_lcu_entry_lightname\">\
                    <property name=\"width_request\">300</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_lcu_entry_tolerance\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">4</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label59\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Mã thiết bị điều khiển:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_lcu_entry_id\">\
                    <property name=\"width_request\">300</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label112\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"yalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Ghi chú:</property>\
                    <property name=\"ellipsize\">end</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">6</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label39\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Sai số công suất (%):</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">4</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label116\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Trạm quản lý:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">5</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_lcu_entry_note\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">6</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"add_lcu_combobox_dcu\">\
                    <property name=\"height_request\">32</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">5</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label67\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Công suất đèn(w):</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">3</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"add_lcu_entry_power\">\
                    <property name=\"width_request\">300</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"invisible_char\">●</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">3</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"add_lcu_label_error\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"xalign\">0</property>\
                <attributes>\
                  <attribute name=\"foreground\" value=\"#efef29292929\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-3\">lcu_add_ok</action-widget>\
      <action-widget response=\"-7\">dcu_add_cancel4</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkAdjustment\" id=\"adjustment_hh\">\
    <property name=\"upper\">23</property>\
    <property name=\"step_increment\">1</property>\
    <property name=\"page_increment\">10</property>\
  </object>\
  <object class=\"GtkAdjustment\" id=\"adjustment_mm\">\
    <property name=\"upper\">59</property>\
    <property name=\"step_increment\">1</property>\
    <property name=\"page_increment\">10</property>\
  </object>\
  <object class=\"GtkAdjustment\" id=\"adjustment_ss\">\
    <property name=\"upper\">59</property>\
    <property name=\"step_increment\">1</property>\
    <property name=\"page_increment\">10</property>\
  </object>\
  <object class=\"GtkDialog\" id=\"admin_user_manage_edit_dialog\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox28\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area28\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_left\">10</property>\
            <property name=\"margin_right\">10</property>\
            <property name=\"margin_top\">20</property>\
            <property name=\"margin_bottom\">10</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_update7\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close13\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box68\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_top\">20</property>\
            <property name=\"margin_bottom\">1</property>\
            <property name=\"border_width\">5</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"admin_user_manage_edit_main_label\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_bottom\">20</property>\
                <property name=\"label\" translatable=\"yes\">CHỈNH SỬA THÔNG TIN NGƯỜI DÙNG</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 16\"/>\
                  <attribute name=\"weight\" value=\"bold\"/>\
                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"admin_user_manage_edit_error_label\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">5</property>\
                <property name=\"margin_bottom\">5</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"frame19\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment17\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">5</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"margin_bottom\">5</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box70\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"admin_user_manage_new_grid\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_bottom\">2</property>\
                            <property name=\"row_spacing\">5</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label146\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Tên đăng nhập:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"admin_user_manage_new_account_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"admin_user_manage_edit_grid\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_bottom\">2</property>\
                            <property name=\"row_spacing\">5</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label147\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Tên đăng nhập:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"admin_user_manage_edit_account_label\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid7\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_bottom\">2</property>\
                            <property name=\"row_spacing\">5</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label15\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Mật khẩu:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"admin_user_manage_edit_password_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">2</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"admin_user_manage_edit_retype_passwd_grid\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"admin_user_manage_edit_password_entry_2\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label66\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Nhập lại mật khẩu:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">3</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid27\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_top\">3</property>\
                            <property name=\"row_spacing\">2</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label137\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Số điện thoại:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label138\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Địa chỉ Email:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"admin_user_manage_edit_phone_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"admin_user_manage_edit_email_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">4</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\" id=\"admin_user_manage_edit_id_box\">\
                            <property name=\"sensitive\">False</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label144\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">ID:</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"admin_user_manage_edit_id_label\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">5</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label117\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Thông Tin Cơ Bản</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 12\"/>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"frame9\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">20</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment19\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">5</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"margin_bottom\">5</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box98\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkBox\" id=\"box101\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label140\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"label\" translatable=\"yes\">Phân mức đặc quyền:</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkComboBoxText\" id=\"admin_user_manage_edit_level_comboboxtext\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"margin_left\">10</property>\
                                <property name=\"margin_right\">10</property>\
                                <property name=\"margin_top\">5</property>\
                                <property name=\"margin_bottom\">5</property>\
                                <items>\
                                  <item translatable=\"yes\">Người Dùng Bình Thường</item>\
                                  <item translatable=\"yes\">Người Dùng Đặc Biệt</item>\
                                </items>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">True</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\" id=\"admin_user_manage_edit_manage_dcu_box\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_top\">10</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_manage_dcu_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Quản lý trạm DCU</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid28\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_top\">10</property>\
                            <property name=\"row_spacing\">10</property>\
                            <property name=\"row_homogeneous\">True</property>\
                            <property name=\"column_homogeneous\">True</property>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_manage_lcu_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Quản lý LCU/LINE</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_create_program_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Tạo lập lịch</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_setup_device_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Thiết lập thiết bị</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_control_lcu_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Điều khiển LCU/LINE</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">2</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid30\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_email_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Nhận email thông báo sự kiện mới.</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"margin_top\">5</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_sms_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Nhận tin nhắn SMS thông báo sự kiện mới.</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"margin_top\">5</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">3</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label142\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">2</property>\
                    <property name=\"label\" translatable=\"yes\">Thông Tin Đặc Quyền</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 12\"/>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"frame8\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">20</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment18\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">5</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"margin_bottom\">5</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box83\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid29\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_top\">5</property>\
                            <property name=\"row_spacing\">5</property>\
                            <property name=\"column_spacing\">2</property>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_email_notify_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Nhận thông tin cảnh bảo thông qua email đã cung cấp.</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"admin_user_manage_edit_sms_notify_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Nhận thông tin cảnh bảo bằng sms gửi đến số điện thoại đã cung cấp.</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label139\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Thông Tin Cấu Hình</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 12\"/>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">4</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"2\">lcu_update7</action-widget>\
      <action-widget response=\"1\">lcu_close13</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"admin_zone_edit_dialog\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"modal\">True</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox35\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area35\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_left\">10</property>\
            <property name=\"margin_right\">10</property>\
            <property name=\"margin_top\">10</property>\
            <property name=\"margin_bottom\">10</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_update8\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close14\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box112\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"admin_zone_edit_main_label\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">20</property>\
                <property name=\"margin_bottom\">20</property>\
                <property name=\"label\" translatable=\"yes\">TẠO MỚI KHU VỰC</property>\
                <property name=\"angle\">0.11</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"Bitstream Vera Serif 16\"/>\
                  <attribute name=\"weight\" value=\"bold\"/>\
                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"admin_zone_edit_error_label\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_bottom\">10</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkGrid\" id=\"grid23\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">10</property>\
                <property name=\"margin_right\">10</property>\
                <property name=\"margin_top\">10</property>\
                <property name=\"margin_bottom\">10</property>\
                <property name=\"row_spacing\">10</property>\
                <property name=\"column_spacing\">10</property>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label153\">\
                    <property name=\"width_request\">100</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Tên khu vực:</property>\
                    <property name=\"ellipsize\">end</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label155\">\
                    <property name=\"width_request\">100</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Ghi chú:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"admin_zone_edit_name_entry\">\
                    <property name=\"width_request\">400</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"admin_zone_edit_note_entry\">\
                    <property name=\"width_request\">400</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"admin_zone_edit_id\">\
                <property name=\"sensitive\">False</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">\
</property>\
                <property name=\"ellipsize\">end</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"2\">lcu_update8</action-widget>\
      <action-widget response=\"1\">lcu_close14</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"create_schedule_dialog\">\
    <property name=\"width_request\">350</property>\
    <property name=\"height_request\">150</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"type\">popup</property>\
    <property name=\"title\" translatable=\"yes\">Tạo mới chương trình</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"window_position\">center-always</property>\
    <property name=\"default_width\">350</property>\
    <property name=\"default_height\">150</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox6\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area6\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_top\">10</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close3\">\
                <property name=\"label\" translatable=\"yes\">OK</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close4\">\
                <property name=\"label\" translatable=\"yes\">Hủy</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">2</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkLabel\" id=\"add_program_label_error\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_left\">5</property>\
            <property name=\"margin_right\">5</property>\
            <property name=\"margin_top\">5</property>\
            <property name=\"margin_bottom\">5</property>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box31\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_left\">10</property>\
            <property name=\"margin_right\">10</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"label34\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"xalign\">0</property>\
                <property name=\"label\" translatable=\"yes\">Tên chương trình:</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">False</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkEntry\" id=\"new_program_entry_name\">\
                <property name=\"width_request\">200</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"margin_left\">10</property>\
                <property name=\"invisible_char\">●</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">False</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"2\">lcu_close3</action-widget>\
      <action-widget response=\"1\">lcu_close4</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"devices_log_dialog\">\
    <property name=\"width_request\">710</property>\
    <property name=\"height_request\">400</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"default_width\">710</property>\
    <property name=\"default_height\">400</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox20\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area20\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close7\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box49\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkBox\" id=\"box56\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label63\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">5</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"margin_bottom\">5</property>\
                    <property name=\"label\" translatable=\"yes\">NHẬT KÝ HOẠT ĐỘNG CỦA THIẾT BỊ</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 16\"/>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"dcu_log_connect_dcu_id\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">5</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"margin_bottom\">20</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkNotebook\" id=\"notebook1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"box51\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box54\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow14\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"shadow_type\">in</property>\
                        <child>\
                          <object class=\"GtkTreeView\" id=\"dcu_log_connect_treeview\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"rules_hint\">True</property>\
                            <child internal-child=\"selection\">\
                              <object class=\"GtkTreeSelection\" id=\"treeview-selection6\"/>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"tab\">\
                  <object class=\"GtkLabel\" id=\"label55\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Nhật Ký Kết Nối</property>\
                  </object>\
                  <packing>\
                    <property name=\"tab_fill\">False</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\" id=\"box52\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box16\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow15\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"shadow_type\">in</property>\
                        <child>\
                          <object class=\"GtkTreeView\" id=\"dcu_log_dcu_treeview\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"rules_hint\">True</property>\
                            <child internal-child=\"selection\">\
                              <object class=\"GtkTreeSelection\" id=\"treeview-selection7\"/>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child type=\"tab\">\
                  <object class=\"GtkLabel\" id=\"label60\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Hoạt Động Trạm</property>\
                  </object>\
                  <packing>\
                    <property name=\"position\">1</property>\
                    <property name=\"tab_fill\">False</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\" id=\"box53\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box17\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow16\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"shadow_type\">in</property>\
                        <child>\
                          <object class=\"GtkTreeView\" id=\"dcu_log_lcu_treeview\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"rules_hint\">True</property>\
                            <child internal-child=\"selection\">\
                              <object class=\"GtkTreeSelection\" id=\"treeview-selection8\"/>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
                <child type=\"tab\">\
                  <object class=\"GtkLabel\" id=\"label62\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Hoạt Động Đèn</property>\
                  </object>\
                  <packing>\
                    <property name=\"position\">2</property>\
                    <property name=\"tab_fill\">False</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\" id=\"box61\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box30\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow17\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"shadow_type\">in</property>\
                        <child>\
                          <object class=\"GtkTreeView\" id=\"dcu_log_line_treeview\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"rules_hint\">True</property>\
                            <child internal-child=\"selection\">\
                              <object class=\"GtkTreeSelection\" id=\"treeview-selection9\"/>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"position\">3</property>\
                  </packing>\
                </child>\
                <child type=\"tab\">\
                  <object class=\"GtkLabel\" id=\"label64\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Hoạt Động LINE</property>\
                  </object>\
                  <packing>\
                    <property name=\"position\">3</property>\
                    <property name=\"tab_fill\">False</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">lcu_close7</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"dlg_select_program_day\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox33\">\
        <property name=\"width_request\">300</property>\
        <property name=\"height_request\">250</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area33\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"button2\">\
                <property name=\"label\" translatable=\"yes\">Chọn</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"button3\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkScrolledWindow\" id=\"scrolledwindow11\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">True</property>\
            <property name=\"border_width\">4</property>\
            <property name=\"shadow_type\">in</property>\
            <child>\
              <object class=\"GtkTreeView\" id=\"dlg_select_treeview\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"headers_visible\">False</property>\
                <property name=\"rules_hint\">True</property>\
                <property name=\"enable_search\">False</property>\
                <property name=\"show_expanders\">False</property>\
                <child internal-child=\"selection\">\
                  <object class=\"GtkTreeSelection\" id=\"treeview-selection30\"/>\
                </child>\
              </object>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">button2</action-widget>\
      <action-widget response=\"-7\">button3</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkImage\" id=\"image_add\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/add.png</property>\
  </object>\
  <object class=\"GtkImage\" id=\"image_add1\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/add.png</property>\
  </object>\
  <object class=\"GtkImage\" id=\"image_edit\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/edit.png</property>\
  </object>\
  <object class=\"GtkImage\" id=\"image_edit1\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/edit.png</property>\
  </object>\
  <object class=\"GtkImage\" id=\"image_edit2\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/edit.png</property>\
  </object>\
  <object class=\"GtkImage\" id=\"image_remove\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/remove.png</property>\
  </object>\
  <object class=\"GtkImage\" id=\"image_remove1\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/remove.png</property>\
  </object>\
  <object class=\"GtkWindow\" id=\"main_window\">\
    <property name=\"width_request\">800</property>\
    <property name=\"height_request\">500</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"title\" translatable=\"yes\">Smart Street Light System Manager</property>\
    <property name=\"window_position\">center-always</property>\
    <property name=\"decorated\">False</property>\
    <child>\
      <object class=\"GtkBox\" id=\"box5\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <child>\
          <object class=\"GtkBox\" id=\"box6\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"box58\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"box_placehold_2\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label_placehold_1\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label6\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">20</property>\
                    <property name=\"margin_bottom\">5</property>\
                    <property name=\"hexpand\">True</property>\
                    <property name=\"label\" translatable=\"yes\">HỆ THỐNG QUẢN LÝ ĐÈN ĐƯỜNG THÔNG MINH</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"Sans 14\"/>\
                      <attribute name=\"weight\" value=\"heavy\"/>\
                      <attribute name=\"foreground\" value=\"#45686848f859\"/>\
                    </attributes>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\" id=\"box_placehold_1\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_right\">10</property>\
                    <child>\
                      <object class=\"GtkButton\" id=\"main_window_quit_button\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"can_default\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"tooltip_text\" translatable=\"yes\">Thoát ứng dụng</property>\
                        <property name=\"margin_left\">5</property>\
                        <property name=\"margin_bottom\">25</property>\
                        <property name=\"relief\">none</property>\
                        <property name=\"xalign\">0.55999994277954102</property>\
                        <property name=\"yalign\">0.55000001192092896</property>\
                        <property name=\"always_show_image\">True</property>\
                        <child>\
                          <object class=\"GtkImage\" id=\"image2\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"stock\">gtk-close</property>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"pack_type\">end</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"btn_show_notify\">\
                        <property name=\"name\">notification_btn</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"margin_top\">15</property>\
                        <property name=\"relief\">none</property>\
                        <property name=\"focus_on_click\">False</property>\
                        <child>\
                          <object class=\"GtkFixed\" id=\"fixed5\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkImage\" id=\"image_notification\">\
                                <property name=\"width_request\">32</property>\
                                <property name=\"height_request\">32</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"pixbuf\">icons/32x32/notication.png</property>\
                              </object>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"notification_lb\">\
                                <property name=\"name\">notification_lb</property>\
                                <property name=\"width_request\">32</property>\
                                <property name=\"height_request\">32</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"margin_left\">3</property>\
                                <property name=\"margin_bottom\">10</property>\
                                <property name=\"label\" translatable=\"yes\">0</property>\
                              </object>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"pack_type\">end</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"user_login_button\">\
                        <property name=\"label\" translatable=\"yes\">Đăng xuất</property>\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"name\">logout_btn</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"margin_right\">20</property>\
                        <property name=\"margin_top\">25</property>\
                        <property name=\"margin_bottom\">5</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"pack_type\">end</property>\
                        <property name=\"position\">2</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLinkButton\" id=\"current_username_login\">\
                        <property name=\"label\" translatable=\"yes\">user</property>\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"name\">username_btn</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"has_tooltip\">True</property>\
                        <property name=\"margin_top\">20</property>\
                        <property name=\"relief\">none</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"pack_type\">end</property>\
                        <property name=\"position\">3</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkNotebook\" id=\"main_notebook\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">True</property>\
            <child>\
              <object class=\"GtkBox\" id=\"box1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_bottom\">2</property>\
                <property name=\"homogeneous\">True</property>\
                <child>\
                  <object class=\"GtkPaned\" id=\"paned1\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"position\">200</property>\
                    <property name=\"position_set\">True</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box2\">\
                        <property name=\"width_request\">200</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_bottom\">3</property>\
                        <property name=\"spacing\">8</property>\
                        <child>\
                          <object class=\"GtkNotebook\" id=\"notebook_manager_dcu\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"margin_top\">9</property>\
                            <child>\
                              <object class=\"GtkBox\" id=\"box74\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"border_width\">5</property>\
                                <property name=\"orientation\">vertical</property>\
                                <property name=\"spacing\">3</property>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box75\">\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"no_show_all\">True</property>\
                                    <property name=\"spacing\">3</property>\
                                    <child>\
                                      <placeholder/>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkButton\" id=\"btn_dcu_search\">\
                                        <property name=\"use_action_appearance\">False</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"receives_default\">True</property>\
                                        <child>\
                                          <object class=\"GtkImage\" id=\"image_search\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"pixbuf\">../icons/16x16/find.png</property>\
                                            <property name=\"icon_size\">0</property>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkScrolledWindow\" id=\"scrolledwindow19\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"shadow_type\">in</property>\
                                    <child>\
                                      <object class=\"GtkTreeView\" id=\"dcu_info_tree_view\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"rules_hint\">True</property>\
                                        <property name=\"search_column\">2</property>\
                                        <child internal-child=\"selection\">\
                                          <object class=\"GtkTreeSelection\" id=\"treeview-selection27\"/>\
                                        </child>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkFrame\" id=\"frame1\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"label_xalign\">0</property>\
                                    <property name=\"shadow_type\">in</property>\
                                    <child>\
                                      <object class=\"GtkAlignment\" id=\"alignment5\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"left_padding\">3</property>\
                                        <child>\
                                          <object class=\"GtkBox\" id=\"box77\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"border_width\">2</property>\
                                            <property name=\"orientation\">vertical</property>\
                                            <child>\
                                              <object class=\"GtkLabel\" id=\"lb_dcu_id\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"label\" translatable=\"yes\">Chưa được chọn</property>\
                                                <attributes>\
                                                  <attribute name=\"weight\" value=\"bold\"/>\
                                                  <attribute name=\"foreground\" value=\"#72729f9fcfcf\"/>\
                                                </attributes>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkGrid\" id=\"grid12\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"margin_bottom\">2</property>\
                                                <property name=\"row_spacing\">2</property>\
                                                <property name=\"column_spacing\">2</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label79\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Khu vực:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">4</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label80\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">GPS:</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">5</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label81\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Địa chỉ:</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">6</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label82\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Ghi chú:</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">7</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_zone\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">4</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_location\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">5</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_address\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                    <property name=\"wrap\">True</property>\
                                                    <property name=\"ellipsize\">end</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">6</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_note\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">7</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_mode\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label75\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Chế độ:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label78\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Trạng thái:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">1</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_status\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">1</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label77\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Số thuê bao:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">3</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_phone\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">3</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label141\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Kết nối:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">2</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_dcu_connect\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">2</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label84\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Chương trình:</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">8</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"cbb_program_name\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">8</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">False</property>\
                                                <property name=\"position\">2</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                    </child>\
                                    <child type=\"label\">\
                                      <object class=\"GtkLabel\" id=\"label143\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">Thông tin chi tiết</property>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">2</property>\
                                  </packing>\
                                </child>\
                              </object>\
                            </child>\
                            <child type=\"tab\">\
                              <object class=\"GtkLabel\" id=\"label73\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"label\" translatable=\"yes\">Trạm</property>\
                              </object>\
                              <packing>\
                                <property name=\"tab_fill\">False</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkBox\" id=\"box73\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"border_width\">5</property>\
                                <property name=\"orientation\">vertical</property>\
                                <property name=\"spacing\">3</property>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box76\">\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"no_show_all\">True</property>\
                                    <property name=\"spacing\">3</property>\
                                    <child>\
                                      <placeholder/>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkButton\" id=\"btn_light_search\">\
                                        <property name=\"use_action_appearance\">False</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"receives_default\">True</property>\
                                        <child>\
                                          <object class=\"GtkImage\" id=\"image_search1\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"pixbuf\">../icons/16x16/find.png</property>\
                                            <property name=\"icon_size\">0</property>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkScrolledWindow\" id=\"scrolledwindow20\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"shadow_type\">in</property>\
                                    <child>\
                                      <object class=\"GtkViewport\" id=\"viewport8\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <child>\
                                          <object class=\"GtkBox\" id=\"box72\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"orientation\">vertical</property>\
                                            <child>\
                                              <object class=\"GtkTreeView\" id=\"light_info_tree_view\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">True</property>\
                                                <property name=\"rules_hint\">True</property>\
                                                <child internal-child=\"selection\">\
                                                  <object class=\"GtkTreeSelection\" id=\"treeview-selection28\"/>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">True</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">0</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkTreeView\" id=\"light_hidden_info_tree_view\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">True</property>\
                                                <property name=\"headers_visible\">False</property>\
                                                <property name=\"rules_hint\">True</property>\
                                                <child internal-child=\"selection\">\
                                                  <object class=\"GtkTreeSelection\" id=\"treeview-selection2\"/>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">True</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkFrame\" id=\"frame2\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"label_xalign\">0</property>\
                                    <property name=\"shadow_type\">in</property>\
                                    <child>\
                                      <object class=\"GtkAlignment\" id=\"alignment6\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"margin_left\">5</property>\
                                        <property name=\"margin_right\">5</property>\
                                        <property name=\"margin_top\">5</property>\
                                        <property name=\"margin_bottom\">5</property>\
                                        <property name=\"left_padding\">3</property>\
                                        <child>\
                                          <object class=\"GtkBox\" id=\"box78\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"border_width\">2</property>\
                                            <property name=\"orientation\">vertical</property>\
                                            <child>\
                                              <object class=\"GtkLabel\" id=\"lb_lcu_id\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"label\" translatable=\"yes\">Id đèn</property>\
                                                <attributes>\
                                                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 12\"/>\
                                                  <attribute name=\"weight\" value=\"bold\"/>\
                                                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                                                </attributes>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkGrid\" id=\"grid13\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"margin_bottom\">2</property>\
                                                <property name=\"orientation\">vertical</property>\
                                                <property name=\"row_spacing\">2</property>\
                                                <property name=\"column_spacing\">2</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label76\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Chế độ:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">3</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label87\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">GPS:</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">2</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label85\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Trạng thái:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">1</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_mode\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">3</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_gps\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">2</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_status\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">1</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label61\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Loại đèn:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_lightname\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label86\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Ghi chú:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">8</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_note\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">8</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label68\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Công suất đèn:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">6</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label88\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Cống suất hiện tại:</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">5</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label89\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Mức sáng:</property>\
                                                    <property name=\"angle\">0.02</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">4</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_level\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">4</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_vol\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">5</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_power\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">6</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label69\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Sai số cho phép:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">7</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"lb_lcd_tolerance\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">undefine</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">7</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">False</property>\
                                                <property name=\"position\">2</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkBox\" id=\"box79\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <child>\
                                                  <placeholder/>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkSwitch\" id=\"switch_light\">\
                                                    <property name=\"use_action_appearance\">False</property>\
                                                    <property name=\"width_request\">50</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"sensitive\">False</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"margin_bottom\">5</property>\
                                                    <property name=\"active\">True</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">False</property>\
                                                    <property name=\"fill\">False</property>\
                                                    <property name=\"pack_type\">end</property>\
                                                    <property name=\"position\">1</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">3</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                    </child>\
                                    <child type=\"label\">\
                                      <object class=\"GtkLabel\" id=\"label92\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">Thông tin chi tiết</property>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">2</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                            <child type=\"tab\">\
                              <object class=\"GtkLabel\" id=\"label74\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"label\" translatable=\"yes\">Đèn</property>\
                              </object>\
                              <packing>\
                                <property name=\"position\">1</property>\
                                <property name=\"tab_fill\">False</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"resize\">True</property>\
                        <property name=\"shrink\">False</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box36\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"hexpand\">True</property>\
                        <property name=\"vexpand\">True</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkBox\" id=\"box25\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"border_width\">10</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <object class=\"GtkBox\" id=\"box38\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"orientation\">vertical</property>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"map_box\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"orientation\">vertical</property>\
                                    <child>\
                                      <placeholder/>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"map_control_box\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"spacing\">2</property>\
                                    <child>\
                                      <object class=\"GtkBox\" id=\"map_provider\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"margin_bottom\">1</property>\
                                        <property name=\"spacing\">3</property>\
                                        <child>\
                                          <object class=\"GtkLabel\" id=\"label51\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label\" translatable=\"yes\">Bản Đồ:</property>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">0</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkComboBoxText\" id=\"comboboxtext_choose_map\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"active\">0</property>\
                                            <items>\
                                              <item translatable=\"yes\">Google Street Map</item>\
                                              <item translatable=\"yes\">Google Satellite</item>\
                                              <item translatable=\"yes\">Open Street Map</item>\
                                              <item translatable=\"yes\">Open Street Map Renderer</item>\
                                              <item translatable=\"yes\">Open Aerial Map</item>\
                                              <item translatable=\"yes\">Map For Free</item>\
                                              <item translatable=\"yes\">Open CyCle Map</item>\
                                              <item translatable=\"yes\">OSM Public TRansport</item>\
                                              <item translatable=\"yes\">Google Hybrid Map</item>\
                                              <item translatable=\"yes\">Virtual Earth Street</item>\
                                              <item translatable=\"yes\">Virtual Earth Satellite</item>\
                                              <item translatable=\"yes\">Virtual Earth Hybrid</item>\
                                              <item translatable=\"yes\">OSMC Trails</item>\
                                            </items>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">1</property>\
                                          </packing>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkBox\" id=\"box80\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"spacing\">2</property>\
                                        <child>\
                                          <object class=\"GtkLabel\" id=\"label90\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label\" translatable=\"yes\">Hiển thị đèn:</property>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">0</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkComboBoxText\" id=\"cbb_light_display\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"active\">2</property>\
                                            <property name=\"active_id\">0</property>\
                                            <items>\
                                              <item translatable=\"yes\">Theo trạm</item>\
                                              <item translatable=\"yes\">Theo khu vực</item>\
                                            </items>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">1</property>\
                                          </packing>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkButton\" id=\"zoom_in_button\">\
                                        <property name=\"use_action_appearance\">False</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"receives_default\">True</property>\
                                        <property name=\"has_tooltip\">True</property>\
                                        <property name=\"tooltip_markup\" translatable=\"yes\">Zoom in</property>\
                                        <property name=\"tooltip_text\" translatable=\"yes\">Zoom in</property>\
                                        <child>\
                                          <object class=\"GtkImage\" id=\"image_zoom_in\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"pixbuf\">../icons/32x32/zoom_in.png</property>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">2</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkButton\" id=\"zoom_out_button\">\
                                        <property name=\"use_action_appearance\">False</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"receives_default\">True</property>\
                                        <property name=\"has_tooltip\">True</property>\
                                        <property name=\"tooltip_markup\" translatable=\"yes\">Zoom out</property>\
                                        <property name=\"tooltip_text\" translatable=\"yes\">Zoom out</property>\
                                        <child>\
                                          <object class=\"GtkImage\" id=\"image_zoom_out\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"pixbuf\">../icons/32x32/zoom_out.png</property>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">3</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkButton\" id=\"home_button\">\
                                        <property name=\"use_action_appearance\">False</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"receives_default\">True</property>\
                                        <property name=\"has_tooltip\">True</property>\
                                        <property name=\"tooltip_markup\" translatable=\"yes\">Home</property>\
                                        <property name=\"tooltip_text\" translatable=\"yes\">Home</property>\
                                        <child>\
                                          <object class=\"GtkImage\" id=\"image_home\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"pixbuf\">../icons/32x32/home.png</property>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">4</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">2</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box45\">\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"no_show_all\">True</property>\
                                    <child>\
                                      <object class=\"GtkEntry\" id=\"text_entry\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"invisible_char\">•</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkLabel\" id=\"cache_label\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"xalign\">1</property>\
                                        <property name=\"label\" translatable=\"yes\">0</property>\
                                        <property name=\"width_chars\">5</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">3</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkExpander\" id=\"expander1\">\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"no_show_all\">True</property>\
                                    <property name=\"margin_top\">5</property>\
                                    <property name=\"margin_bottom\">5</property>\
                                    <child>\
                                      <object class=\"GtkAlignment\" id=\"alignment2\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"left_padding\">4</property>\
                                        <child>\
                                          <object class=\"GtkVBox\" id=\"vbox2\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <child>\
                                              <object class=\"GtkHBox\" id=\"hbox1\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"spacing\">4</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label41\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Color</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">False</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkColorButton\" id=\"gps_colorbutton\">\
                                                    <property name=\"use_action_appearance\">False</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"receives_default\">True</property>\
                                                    <property name=\"color\">#000000000000</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">True</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">1</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">False</property>\
                                                <property name=\"position\">0</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkHBox\" id=\"hbox4\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"spacing\">4</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label44\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Alpha</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">False</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkHScale\" id=\"hscale1\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"restrict_to_fill_level\">False</property>\
                                                    <property name=\"fill_level\">0</property>\
                                                    <property name=\"draw_value\">False</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">True</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">1</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">False</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkHBox\" id=\"hbox5\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"spacing\">4</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label45\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Width</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">False</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkHScale\" id=\"hscale2\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"restrict_to_fill_level\">False</property>\
                                                    <property name=\"fill_level\">0</property>\
                                                    <property name=\"draw_value\">False</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">True</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">1</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">False</property>\
                                                <property name=\"position\">2</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                    </child>\
                                    <child type=\"label\">\
                                      <object class=\"GtkLabel\" id=\"label46\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">GPS Track Appearance</property>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">False</property>\
                                    <property name=\"position\">4</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkExpander\" id=\"expander2\">\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"no_show_all\">True</property>\
                                    <property name=\"margin_top\">5</property>\
                                    <property name=\"margin_bottom\">5</property>\
                                    <child>\
                                      <object class=\"GtkAlignment\" id=\"alignment3\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"left_padding\">4</property>\
                                        <child>\
                                          <object class=\"GtkVBox\" id=\"vbox3\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <child>\
                                              <object class=\"GtkHBox\" id=\"hbox6\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"spacing\">4</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label47\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">X Offset</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">False</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkHScale\" id=\"hscale3\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"restrict_to_fill_level\">False</property>\
                                                    <property name=\"fill_level\">0</property>\
                                                    <property name=\"draw_value\">False</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">True</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">1</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">False</property>\
                                                <property name=\"position\">0</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkHBox\" id=\"hbox7\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"spacing\">4</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label48\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Y Offset</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">False</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkHScale\" id=\"hscale4\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"restrict_to_fill_level\">False</property>\
                                                    <property name=\"fill_level\">0</property>\
                                                    <property name=\"draw_value\">False</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">True</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">1</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">False</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                    </child>\
                                    <child type=\"label\">\
                                      <object class=\"GtkLabel\" id=\"label49\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">Star Image Appearance</property>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">False</property>\
                                    <property name=\"position\">5</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">True</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkBox\" id=\"box42\">\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"no_show_all\">True</property>\
                                <property name=\"orientation\">vertical</property>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box43\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <child>\
                                      <object class=\"GtkLabel\" id=\"label14\">\
                                        <property name=\"width_request\">100</property>\
                                        <property name=\"height_request\">0</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">Lattitube:</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkEntry\" id=\"entry_text_lat\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"invisible_char\">●</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box44\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <child>\
                                      <object class=\"GtkLabel\" id=\"label50\">\
                                        <property name=\"width_request\">100</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">Longtitube:</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkEntry\" id=\"entry_text_long\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"invisible_char\">●</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box46\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <child>\
                                      <object class=\"GtkComboBoxText\" id=\"combobox_choose_light\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <items>\
                                          <item translatable=\"yes\">On</item>\
                                          <item translatable=\"yes\">Off</item>\
                                          <item translatable=\"yes\">Broken</item>\
                                        </items>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkBox\" id=\"box47\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <child>\
                                          <object class=\"GtkButton\" id=\"button_remove_light\">\
                                            <property name=\"label\" translatable=\"yes\">Remove All</property>\
                                            <property name=\"use_action_appearance\">False</property>\
                                            <property name=\"width_request\">100</property>\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">True</property>\
                                            <property name=\"receives_default\">True</property>\
                                            <property name=\"relief\">none</property>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">0</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkButton\" id=\"button_add_light\">\
                                            <property name=\"label\" translatable=\"yes\">Add</property>\
                                            <property name=\"use_action_appearance\">False</property>\
                                            <property name=\"width_request\">100</property>\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">True</property>\
                                            <property name=\"receives_default\">True</property>\
                                            <property name=\"relief\">none</property>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">1</property>\
                                          </packing>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">2</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"resize\">True</property>\
                        <property name=\"shrink\">False</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"padding\">1</property>\
                    <property name=\"pack_type\">end</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"notebook_dcu_manager\">\
                <property name=\"width_request\">150</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Quản Lý Trạm</property>\
              </object>\
              <packing>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"box97\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"box23\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"border_width\">3</property>\
                    <property name=\"spacing\">2</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box99\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkLabel\" id=\"label99\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_top\">10</property>\
                            <property name=\"margin_bottom\">10</property>\
                            <property name=\"label\" translatable=\"yes\">Danh sách chương trình lập lịch</property>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\" id=\"box100\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"border_width\">5</property>\
                            <child>\
                              <placeholder/>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkScrolledWindow\" id=\"scrolledwindow24\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"shadow_type\">in</property>\
                            <child>\
                              <object class=\"GtkTreeView\" id=\"program_year_schedule_treeview\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"rules_hint\">True</property>\
                                <child internal-child=\"selection\">\
                                  <object class=\"GtkTreeSelection\" id=\"treeview-selection38\"/>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">2</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkFrame\" id=\"frame5\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label_xalign\">0</property>\
                        <property name=\"shadow_type\">in</property>\
                        <child>\
                          <object class=\"GtkAlignment\" id=\"alignment14\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkBox\" id=\"box103\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"border_width\">3</property>\
                                <property name=\"spacing\">2</property>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box106\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"margin_top\">20</property>\
                                    <property name=\"orientation\">vertical</property>\
                                    <child>\
                                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow8\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">True</property>\
                                        <property name=\"margin_left\">12</property>\
                                        <property name=\"hscrollbar_policy\">never</property>\
                                        <property name=\"shadow_type\">in</property>\
                                        <child>\
                                          <object class=\"GtkTreeView\" id=\"program_month_schedule_treeview\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">True</property>\
                                            <property name=\"rules_hint\">True</property>\
                                            <child internal-child=\"selection\">\
                                              <object class=\"GtkTreeSelection\" id=\"treeview-selection32\"/>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkFrame\" id=\"frame7\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"margin_top\">10</property>\
                                        <property name=\"label_xalign\">0</property>\
                                        <property name=\"shadow_type\">none</property>\
                                        <child>\
                                          <object class=\"GtkAlignment\" id=\"alignment16\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"left_padding\">12</property>\
                                            <child>\
                                              <object class=\"GtkScrolledWindow\" id=\"scrolledwindow5\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">True</property>\
                                                <property name=\"shadow_type\">in</property>\
                                                <child>\
                                                  <object class=\"GtkTreeView\" id=\"program_dcu_list_treeview\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"rules_hint\">True</property>\
                                                    <child internal-child=\"selection\">\
                                                      <object class=\"GtkTreeSelection\" id=\"treeview-selection33\"/>\
                                                    </child>\
                                                  </object>\
                                                </child>\
                                              </object>\
                                            </child>\
                                          </object>\
                                        </child>\
                                        <child type=\"label\">\
                                          <object class=\"GtkLabel\" id=\"label9\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label\" translatable=\"yes\">Danh sách trạm hoạt động theo chương trình này</property>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">True</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkFrame\" id=\"frame6\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"label_xalign\">0</property>\
                                    <property name=\"shadow_type\">none</property>\
                                    <child>\
                                      <object class=\"GtkAlignment\" id=\"alignment15\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"left_padding\">12</property>\
                                        <child>\
                                          <object class=\"GtkScrolledWindow\" id=\"scrolledwindow4\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">True</property>\
                                            <property name=\"hscrollbar_policy\">never</property>\
                                            <property name=\"vscrollbar_policy\">never</property>\
                                            <property name=\"shadow_type\">in</property>\
                                            <child>\
                                              <object class=\"GtkViewport\" id=\"viewport1\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <child>\
                                                  <object class=\"GtkBox\" id=\"box9\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"orientation\">vertical</property>\
                                                    <child>\
                                                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow7\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">True</property>\
                                                        <child>\
                                                          <object class=\"GtkTreeView\" id=\"program_item_schedule_treeview\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"rules_hint\">True</property>\
                                                            <property name=\"enable_tree_lines\">True</property>\
                                                            <child internal-child=\"selection\">\
                                                            <object class=\"GtkTreeSelection\" id=\"treeview-selection29\"/>\
                                                            </child>\
                                                          </object>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">True</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">0</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkButtonBox\" id=\"buttonbox3\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <property name=\"border_width\">3</property>\
                                                        <property name=\"layout_style\">end</property>\
                                                        <child>\
                                                          <object class=\"GtkButton\" id=\"schedule_btn_add\">\
                                                            <property name=\"label\" translatable=\"yes\">Thêm mới</property>\
                                                            <property name=\"use_action_appearance\">False</property>\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"receives_default\">True</property>\
                                                            <property name=\"image\">image_add1</property>\
                                                            <property name=\"always_show_image\">True</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">True</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkButton\" id=\"schedule_btn_edit\">\
                                                            <property name=\"label\" translatable=\"yes\">Chỉnh sửa</property>\
                                                            <property name=\"use_action_appearance\">False</property>\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"receives_default\">True</property>\
                                                            <property name=\"image\">image_edit1</property>\
                                                            <property name=\"always_show_image\">True</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">True</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkButton\" id=\"schedule_btn_remove\">\
                                                            <property name=\"label\" translatable=\"yes\">Xóa</property>\
                                                            <property name=\"use_action_appearance\">False</property>\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"receives_default\">True</property>\
                                                            <property name=\"image\">image_remove1</property>\
                                                            <property name=\"always_show_image\">True</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">True</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">2</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">1</property>\
                                                      </packing>\
                                                    </child>\
                                                  </object>\
                                                </child>\
                                              </object>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                    </child>\
                                    <child type=\"label\">\
                                      <object class=\"GtkLabel\" id=\"label136\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">Danh sách cấu hình chương trình theo ngày</property>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"pack_type\">end</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                        </child>\
                        <child type=\"label\">\
                          <object class=\"GtkLabel\" id=\"label2\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Chi tiết</property>\
                            <property name=\"angle\">0.04999999888241291</property>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <placeholder/>\
                </child>\
              </object>\
              <packing>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"notebook_program_manager\">\
                <property name=\"width_request\">150</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Quản Lý Lập Lịch</property>\
              </object>\
              <packing>\
                <property name=\"position\">1</property>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"spl_user_log_box\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"box64\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box67\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_top\">5</property>\
                        <property name=\"margin_bottom\">5</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\" id=\"box113\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_right\">20</property>\
                    <property name=\"margin_bottom\">6</property>\
                    <property name=\"spacing\">4</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"select_box\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkButton\" id=\"userlog_btn_selection_click\">\
                            <property name=\"use_action_appearance\">False</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"receives_default\">True</property>\
                            <property name=\"margin_left\">20</property>\
                            <child>\
                              <object class=\"GtkImage\" id=\"image_checkbox\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"lb_userlog_cur\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"xalign\">1</property>\
                        <property name=\"label\" translatable=\"yes\">1-100</property>\
                        <attributes>\
                          <attribute name=\"weight\" value=\"bold\"/>\
                        </attributes>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label70\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label\" translatable=\"yes\">trong tổng số</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">2</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"lb_userlog_total\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label\" translatable=\"yes\">999</property>\
                        <attributes>\
                          <attribute name=\"weight\" value=\"bold\"/>\
                        </attributes>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">3</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"btn_userlog_back\">\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <child>\
                          <object class=\"GtkImage\" id=\"image_back\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"pixbuf\">icons/16x16/back.png</property>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">4</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"btn_userlog_next\">\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <child>\
                          <object class=\"GtkImage\" id=\"image_next\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"pixbuf\">icons/16x16/next.png</property>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">5</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkScrolledWindow\" id=\"scrolledwindow3\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"margin_left\">10</property>\
                    <property name=\"shadow_type\">in</property>\
                    <child>\
                      <object class=\"GtkTreeView\" id=\"user_log_treeview\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"rules_hint\">True</property>\
                        <child internal-child=\"selection\">\
                          <object class=\"GtkTreeSelection\" id=\"treeview-selection36\"/>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"notebook_user_manager\">\
                <property name=\"width_request\">150</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Nhật Ký Người Dùng</property>\
              </object>\
              <packing>\
                <property name=\"position\">2</property>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"spl_server_log_box\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"box65\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box66\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_top\">5</property>\
                        <property name=\"margin_bottom\">5</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\" id=\"box84\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_bottom\">6</property>\
                    <property name=\"spacing\">4</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"select_box1\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkButton\" id=\"serverlog_btn_selection_click\">\
                            <property name=\"use_action_appearance\">False</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"receives_default\">True</property>\
                            <property name=\"margin_left\">20</property>\
                            <child>\
                              <object class=\"GtkImage\" id=\"server_image_checkbox\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <placeholder/>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"lb_serverlog_cur\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"xalign\">1</property>\
                        <property name=\"label\" translatable=\"yes\">1-100</property>\
                        <attributes>\
                          <attribute name=\"weight\" value=\"bold\"/>\
                        </attributes>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label163\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label\" translatable=\"yes\">trong tổng số</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">2</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"lb_serverlog_total\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label\" translatable=\"yes\">999</property>\
                        <attributes>\
                          <attribute name=\"weight\" value=\"bold\"/>\
                        </attributes>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">3</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"btn_serverlog_back\">\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <child>\
                          <object class=\"GtkImage\" id=\"image_back1\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"pixbuf\">icons/16x16/back.png</property>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">4</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"btn_serverlog_next\">\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <child>\
                          <object class=\"GtkImage\" id=\"image_next1\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"pixbuf\">icons/16x16/next.png</property>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">5</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">False</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkScrolledWindow\" id=\"scrolledwindow18\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"shadow_type\">in</property>\
                    <child>\
                      <object class=\"GtkTreeView\" id=\"server_log_treeview\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"rules_hint\">True</property>\
                        <child internal-child=\"selection\">\
                          <object class=\"GtkTreeSelection\" id=\"treeview-selection34\"/>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"label65\">\
                <property name=\"width_request\">150</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Nhật Ký Server</property>\
              </object>\
              <packing>\
                <property name=\"position\">3</property>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"box8\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkPaned\" id=\"admin_user_manage_paned\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box94\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkBox\" id=\"box96\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <placeholder/>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkScrolledWindow\" id=\"scrolledwindow21\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"margin_left\">10</property>\
                            <property name=\"margin_right\">10</property>\
                            <property name=\"margin_top\">10</property>\
                            <property name=\"margin_bottom\">10</property>\
                            <property name=\"shadow_type\">in</property>\
                            <child>\
                              <object class=\"GtkTreeView\" id=\"admin_user_treeview\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"rules_hint\">True</property>\
                                <child internal-child=\"selection\">\
                                  <object class=\"GtkTreeSelection\" id=\"treeview-selection\"/>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"resize\">False</property>\
                        <property name=\"shrink\">True</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkPaned\" id=\"admin_user_specific_manage_paned\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkScrolledWindow\" id=\"scrolledwindow22\">\
                            <property name=\"height_request\">200</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"margin_left\">10</property>\
                            <property name=\"margin_right\">10</property>\
                            <property name=\"margin_top\">10</property>\
                            <property name=\"margin_bottom\">10</property>\
                            <property name=\"shadow_type\">in</property>\
                            <child>\
                              <object class=\"GtkViewport\" id=\"viewport2\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"margin_left\">5</property>\
                                <property name=\"margin_right\">5</property>\
                                <property name=\"margin_top\">5</property>\
                                <property name=\"margin_bottom\">5</property>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box102\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"orientation\">vertical</property>\
                                    <child>\
                                      <object class=\"GtkFrame\" id=\"aaaaaaaa\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label_xalign\">0</property>\
                                        <property name=\"shadow_type\">none</property>\
                                        <child>\
                                          <object class=\"GtkAlignment\" id=\"alignment7\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"margin_left\">20</property>\
                                            <property name=\"margin_top\">5</property>\
                                            <property name=\"margin_bottom\">5</property>\
                                            <property name=\"left_padding\">12</property>\
                                            <child>\
                                              <object class=\"GtkGrid\" id=\"grid22\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"margin_top\">5</property>\
                                                <property name=\"margin_bottom\">5</property>\
                                                <property name=\"orientation\">vertical</property>\
                                                <property name=\"row_spacing\">5</property>\
                                                <property name=\"column_spacing\">5</property>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label123\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Tên tài khoản:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label124\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Số điện thoại:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">1</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label125\">\
                                                    <property name=\"width_request\">100</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Địa chỉ email:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">2</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"admin_user_name_label\">\
                                                    <property name=\"width_request\">200</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <attributes>\
                                                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                                                    </attributes>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">0</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"admin_user_phone_label\">\
                                                    <property name=\"width_request\">200</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <attributes>\
                                                      <attribute name=\"foreground\" value=\"#34346565a4a4\"/>\
                                                    </attributes>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">1</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"admin_user_email_label\">\
                                                    <property name=\"width_request\">200</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <attributes>\
                                                      <attribute name=\"foreground\" value=\"#34346565a4a4\"/>\
                                                    </attributes>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">2</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"label83\">\
                                                    <property name=\"width_request\">100</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <property name=\"label\" translatable=\"yes\">Phân mức:</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">3</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"admin_user_level_label\">\
                                                    <property name=\"width_request\">200</property>\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <attributes>\
                                                      <attribute name=\"foreground\" value=\"#34346565a4a4\"/>\
                                                    </attributes>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">1</property>\
                                                    <property name=\"top_attach\">3</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <object class=\"GtkLabel\" id=\"admin_user_id_label\">\
                                                    <property name=\"width_request\">200</property>\
                                                    <property name=\"sensitive\">False</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"no_show_all\">True</property>\
                                                    <property name=\"xalign\">0</property>\
                                                    <attributes>\
                                                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                                                    </attributes>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"left_attach\">0</property>\
                                                    <property name=\"top_attach\">4</property>\
                                                  </packing>\
                                                </child>\
                                                <child>\
                                                  <placeholder/>\
                                                </child>\
                                              </object>\
                                            </child>\
                                          </object>\
                                        </child>\
                                        <child type=\"label\">\
                                          <object class=\"GtkLabel\" id=\"label122\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label\" translatable=\"yes\">Thông tin cơ bản:</property>\
                                            <attributes>\
                                              <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 13\"/>\
                                              <attribute name=\"weight\" value=\"heavy\"/>\
                                              <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                                            </attributes>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkGrid\" id=\"grid20\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <child>\
                                          <object class=\"GtkFrame\" id=\"vvvvvvvvvvvvvvvvv\">\
                                            <property name=\"width_request\">300</property>\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label_xalign\">0</property>\
                                            <property name=\"shadow_type\">none</property>\
                                            <child>\
                                              <object class=\"GtkAlignment\" id=\"alignment8\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"margin_left\">10</property>\
                                                <property name=\"margin_top\">10</property>\
                                                <property name=\"margin_bottom\">5</property>\
                                                <property name=\"left_padding\">12</property>\
                                                <child>\
                                                  <object class=\"GtkBox\" id=\"box108\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"orientation\">vertical</property>\
                                                    <property name=\"spacing\">5</property>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"dcu_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image7\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label18\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Quản lý Trạm DCU</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">0</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"lcu_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image8\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label121\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Quản lý LCU/LINE</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">1</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"lcu_2_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image9\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Điều khiển LCU/LINE</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">2</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"device_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image10\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label148\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Thiết lập thiết bị</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">3</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"program_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image11\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label149\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Quản lý lập lịch</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">4</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"email_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image12\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label150\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Nhận thông báo qua email</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">5</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"sms_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image13\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label151\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Nhận thông báo qua SMS</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">6</property>\
                                                      </packing>\
                                                    </child>\
                                                  </object>\
                                                </child>\
                                              </object>\
                                            </child>\
                                            <child type=\"label\">\
                                              <object class=\"GtkLabel\" id=\"label129\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"label\" translatable=\"yes\">Thông tin đặc quyền:</property>\
                                                <attributes>\
                                                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 13\"/>\
                                                  <attribute name=\"weight\" value=\"heavy\"/>\
                                                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                                                </attributes>\
                                              </object>\
                                            </child>\
                                          </object>\
                                          <packing>\
                                            <property name=\"left_attach\">0</property>\
                                            <property name=\"top_attach\">0</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkFrame\" id=\"vvvvvvvvvvvvvvvvv1\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label_xalign\">0</property>\
                                            <property name=\"shadow_type\">none</property>\
                                            <child>\
                                              <object class=\"GtkAlignment\" id=\"alignment9\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"margin_left\">10</property>\
                                                <property name=\"margin_top\">10</property>\
                                                <property name=\"margin_bottom\">5</property>\
                                                <property name=\"left_padding\">12</property>\
                                                <child>\
                                                  <object class=\"GtkBox\" id=\"box109\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"orientation\">vertical</property>\
                                                    <property name=\"spacing\">5</property>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"email_allow_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image14\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label145\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Cho phép nhận thông báo qua email.</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">0</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"sms_allow_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <child>\
                                                          <object class=\"GtkImage\" id=\"image15\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"margin_right\">10</property>\
                                                            <property name=\"stock\">gtk-apply</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label152\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"label\" translatable=\"yes\">Cho phép nhận thông báo qua tin nhắn SMS</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">1</property>\
                                                      </packing>\
                                                    </child>\
                                                  </object>\
                                                </child>\
                                              </object>\
                                            </child>\
                                            <child type=\"label\">\
                                              <object class=\"GtkLabel\" id=\"label126\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"label\" translatable=\"yes\">Thông tin cấu hình:</property>\
                                                <attributes>\
                                                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 13\"/>\
                                                  <attribute name=\"weight\" value=\"heavy\"/>\
                                                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                                                </attributes>\
                                              </object>\
                                            </child>\
                                          </object>\
                                          <packing>\
                                            <property name=\"left_attach\">1</property>\
                                            <property name=\"top_attach\">0</property>\
                                          </packing>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"resize\">False</property>\
                            <property name=\"shrink\">True</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\" id=\"box3\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <object class=\"GtkScrolledWindow\" id=\"scrolledwindow25\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <child>\
                                  <object class=\"GtkTreeView\" id=\"admin_user_list_zone_treeview\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"rules_hint\">True</property>\
                                    <child internal-child=\"selection\">\
                                      <object class=\"GtkTreeSelection\" id=\"treeview-selection37\"/>\
                                    </child>\
                                  </object>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">True</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkButtonBox\" id=\"buttonbox2\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"border_width\">3</property>\
                                <property name=\"layout_style\">end</property>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"admin_user_zone_own_change_button\">\
                                    <property name=\"label\" translatable=\"yes\">Chỉnh sửa</property>\
                                    <property name=\"use_action_appearance\">False</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"image\">image_edit2</property>\
                                    <property name=\"always_show_image\">True</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"resize\">True</property>\
                            <property name=\"shrink\">True</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"resize\">True</property>\
                        <property name=\"shrink\">True</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"position\">4</property>\
              </packing>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"label7\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Quản Lý Người Dùng</property>\
              </object>\
              <packing>\
                <property name=\"position\">4</property>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"box14\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"box93\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box110\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkPaned\" id=\"admin_zone_manage_paned\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <child>\
                              <object class=\"GtkBox\" id=\"box111\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"orientation\">vertical</property>\
                                <child>\
                                  <object class=\"GtkScrolledWindow\" id=\"scrolledwindow23\">\
                                    <property name=\"width_request\">200</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"margin_left\">10</property>\
                                    <property name=\"margin_right\">10</property>\
                                    <property name=\"margin_top\">10</property>\
                                    <property name=\"margin_bottom\">10</property>\
                                    <property name=\"shadow_type\">in</property>\
                                    <child>\
                                      <placeholder/>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"resize\">False</property>\
                                <property name=\"shrink\">True</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkBox\" id=\"admin_zone_map_box\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"margin_left\">10</property>\
                                <property name=\"margin_right\">10</property>\
                                <property name=\"margin_top\">10</property>\
                                <property name=\"margin_bottom\">10</property>\
                                <property name=\"orientation\">vertical</property>\
                                <child>\
                                  <placeholder/>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"resize\">True</property>\
                                <property name=\"shrink\">True</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"position\">5</property>\
              </packing>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"label10\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Quản Lý Khu Vực</property>\
              </object>\
              <packing>\
                <property name=\"position\">5</property>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
  <object class=\"GtkDialog\" id=\"dialog_change_gps\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"margin_bottom\">1</property>\
    <property name=\"border_width\">3</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"window_position\">center-on-parent</property>\
    <property name=\"destroy_with_parent\">True</property>\
    <property name=\"type_hint\">normal</property>\
    <property name=\"skip_taskbar_hint\">True</property>\
    <property name=\"decorated\">False</property>\
    <property name=\"transient_for\">main_window</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox38\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">3</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area38\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_bottom\">2</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"button1\">\
                <property name=\"label\" translatable=\"yes\">Đồng Ý</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"button4\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box7\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"spacing\">5</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"setting_gps_lb_device\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"xalign\">0</property>\
                <property name=\"label\" translatable=\"yes\">Mã thiết bị:</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"setting_gps_lb_name\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">LB0000001</property>\
                <attributes>\
                  <attribute name=\"weight\" value=\"bold\"/>\
                  <attribute name=\"foreground\" value=\"#8f8f59590202\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"label156\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"xalign\">0</property>\
                <property name=\"label\" translatable=\"yes\">Vĩ độ:</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkEntry\" id=\"setting_gps_entry_lat\">\
                <property name=\"width_request\">100</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"xalign\">1</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"label157\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"xalign\">0</property>\
                <property name=\"label\" translatable=\"yes\">Kinh độ:</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">4</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkEntry\" id=\"setting_gps_entry_lon\">\
                <property name=\"width_request\">100</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"xalign\">1</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">5</property>\
              </packing>\
            </child>\
            <child>\
              <placeholder/>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkScrolledWindow\" id=\"scrolledwindow26\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">True</property>\
            <property name=\"hscrollbar_policy\">never</property>\
            <property name=\"vscrollbar_policy\">never</property>\
            <property name=\"shadow_type\">in</property>\
            <child>\
              <object class=\"GtkViewport\" id=\"viewport5\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"change_gps_map_box\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <placeholder/>\
                    </child>\
                  </object>\
                </child>\
              </object>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">2</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">button1</action-widget>\
      <action-widget response=\"-7\">button4</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkImage\" id=\"image_tick\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"pixbuf\">icons/16x16/tick.png</property>\
  </object>\
  <object class=\"GtkAdjustment\" id=\"lcu_brightness_adjustment\">\
    <property name=\"upper\">10</property>\
    <property name=\"step_increment\">10</property>\
  </object>\
  <object class=\"GtkWindow\" id=\"dcu_control_window\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"modal\">True</property>\
    <property name=\"destroy_with_parent\">True</property>\
    <property name=\"decorated\">False</property>\
    <child>\
      <object class=\"GtkBox\" id=\"box15\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"border_width\">5</property>\
        <property name=\"orientation\">vertical</property>\
        <child>\
          <object class=\"GtkBox\" id=\"box29\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"dcu_control_lb_title\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_bottom\">20</property>\
                <property name=\"label\" translatable=\"yes\">label</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 16\"/>\
                  <attribute name=\"weight\" value=\"bold\"/>\
                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"dcu_control_btn_quit\">\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <property name=\"relief\">none</property>\
                <property name=\"xalign\">0.49000000953674316</property>\
                <property name=\"image_position\">right</property>\
                <child>\
                  <object class=\"GtkImage\" id=\"image6\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">Thoát</property>\
                    <property name=\"stock\">gtk-close</property>\
                    <property name=\"icon_size\">2</property>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box19\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"spacing\">3</property>\
            <child>\
              <object class=\"GtkBox\" id=\"dcu_control_on_off_handle\">\
                <property name=\"width_request\">200</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <property name=\"spacing\">3</property>\
                <child>\
                  <object class=\"GtkFrame\" id=\"frame4\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label_xalign\">0</property>\
                    <property name=\"shadow_type\">in</property>\
                    <child>\
                      <object class=\"GtkAlignment\" id=\"alignment13\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"left_padding\">12</property>\
                        <child>\
                          <object class=\"GtkBox\" id=\"box20\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkBox\" id=\"dcu_control_on_off_box\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"border_width\">5</property>\
                                <property name=\"orientation\">vertical</property>\
                                <property name=\"spacing\">3</property>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"dcu_schedule_program_box\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"orientation\">vertical</property>\
                                    <child>\
                                      <object class=\"GtkLabel\" id=\"label16\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"xalign\">0</property>\
                                        <property name=\"label\" translatable=\"yes\">Chương trình:</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                    <child>\
                                      <object class=\"GtkComboBoxText\" id=\"dcu_schedule_program_comboboxtext\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">1</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">False</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkFrame\" id=\"dcu_control_frame_handle\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"label_xalign\">0</property>\
                                    <property name=\"shadow_type\">out</property>\
                                    <child>\
                                      <object class=\"GtkAlignment\" id=\"alignment12\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"left_padding\">12</property>\
                                        <child>\
                                          <object class=\"GtkBox\" id=\"box21\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"margin_bottom\">3</property>\
                                            <property name=\"border_width\">3</property>\
                                            <property name=\"orientation\">vertical</property>\
                                            <property name=\"spacing\">2</property>\
                                            <child>\
                                              <object class=\"GtkBox\" id=\"box22\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"orientation\">vertical</property>\
                                                <child>\
                                                  <object class=\"GtkComboBoxText\" id=\"dcu_schedule_interleaved_comboboxtext\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">False</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">1</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">0</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkBox\" id=\"dcu_control_box_contain_tree_view\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"orientation\">vertical</property>\
                                                <child>\
                                                  <object class=\"GtkBox\" id=\"dcu_control_box_treeview\">\
                                                    <property name=\"visible\">True</property>\
                                                    <property name=\"can_focus\">False</property>\
                                                    <property name=\"orientation\">vertical</property>\
                                                    <property name=\"spacing\">3</property>\
                                                    <child>\
                                                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow2\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">True</property>\
                                                        <property name=\"shadow_type\">in</property>\
                                                        <child>\
                                                          <object class=\"GtkTreeView\" id=\"dcu_control_treeview\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"rules_hint\">True</property>\
                                                            <child internal-child=\"selection\">\
                                                            <object class=\"GtkTreeSelection\" id=\"treeview-selection24\"/>\
                                                            </child>\
                                                          </object>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">True</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">0</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkBox\" id=\"dcu_control_select_button_box\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <property name=\"spacing\">2</property>\
                                                        <property name=\"homogeneous\">True</property>\
                                                        <child>\
                                                          <object class=\"GtkButton\" id=\"btn_dcu_control_select_all\">\
                                                            <property name=\"label\" translatable=\"yes\">Chọn tất cả</property>\
                                                            <property name=\"use_action_appearance\">False</property>\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"receives_default\">True</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkButton\" id=\"btn_dcu_control_deselect_all\">\
                                                            <property name=\"label\" translatable=\"yes\">Bỏ chọn tất cả</property>\
                                                            <property name=\"use_action_appearance\">False</property>\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"receives_default\">True</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"expand\">False</property>\
                                                            <property name=\"fill\">True</property>\
                                                            <property name=\"position\">1</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">1</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkGrid\" id=\"dcu_manual_level_grid\">\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">False</property>\
                                                        <property name=\"margin_left\">5</property>\
                                                        <property name=\"margin_right\">5</property>\
                                                        <property name=\"margin_top\">5</property>\
                                                        <property name=\"margin_bottom\">5</property>\
                                                        <child>\
                                                          <object class=\"GtkScale\" id=\"dcu_control_lcu_level_scale\">\
                                                            <property name=\"width_request\">200</property>\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">True</property>\
                                                            <property name=\"margin_left\">2</property>\
                                                            <property name=\"adjustment\">lcu_brightness_adjustment</property>\
                                                            <property name=\"fill_level\">10</property>\
                                                            <property name=\"round_digits\">0</property>\
                                                            <property name=\"digits\">0</property>\
                                                            <property name=\"value_pos\">right</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"left_attach\">1</property>\
                                                            <property name=\"top_attach\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                        <child>\
                                                          <object class=\"GtkLabel\" id=\"label135\">\
                                                            <property name=\"visible\">True</property>\
                                                            <property name=\"can_focus\">False</property>\
                                                            <property name=\"tooltip_text\" translatable=\"yes\">Điều chỉnh trong khoảng từ 0 đến 255.</property>\
                                                            <property name=\"margin_right\">26</property>\
                                                            <property name=\"label\" translatable=\"yes\">Cấp độ sáng:</property>\
                                                          </object>\
                                                          <packing>\
                                                            <property name=\"left_attach\">0</property>\
                                                            <property name=\"top_attach\">0</property>\
                                                          </packing>\
                                                        </child>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">2</property>\
                                                      </packing>\
                                                    </child>\
                                                    <child>\
                                                      <object class=\"GtkCheckButton\" id=\"dcu_control_is_temp\">\
                                                        <property name=\"label\" translatable=\"yes\" context=\"xvzvxzvzxvxz\" comments=\"zxvzxvzx\">Phiên làm việc hiện tại</property>\
                                                        <property name=\"use_action_appearance\">False</property>\
                                                        <property name=\"visible\">True</property>\
                                                        <property name=\"can_focus\">True</property>\
                                                        <property name=\"receives_default\">False</property>\
                                                        <property name=\"tooltip_text\" translatable=\"yes\">Có tác dụng trong phiên làm việc hiện tại.\
Khi đăng xuất sẽ khôi phục lại trạng thái ban đầu.</property>\
                                                        <property name=\"xalign\">0.0099999997764825821</property>\
                                                        <property name=\"draw_indicator\">True</property>\
                                                      </object>\
                                                      <packing>\
                                                        <property name=\"expand\">False</property>\
                                                        <property name=\"fill\">True</property>\
                                                        <property name=\"position\">4</property>\
                                                      </packing>\
                                                    </child>\
                                                  </object>\
                                                  <packing>\
                                                    <property name=\"expand\">True</property>\
                                                    <property name=\"fill\">True</property>\
                                                    <property name=\"position\">0</property>\
                                                  </packing>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">True</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                    </child>\
                                    <child type=\"label\">\
                                      <object class=\"GtkLabel\" id=\"dcu_control_core_frame_label\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"label\" translatable=\"yes\">Điều khiển bằng tay</property>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">True</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkBox\" id=\"dcu_schedule_interleaved_box\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"orientation\">vertical</property>\
                                <child>\
                                  <placeholder/>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">False</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                    </child>\
                    <child type=\"label\">\
                      <object class=\"GtkLabel\" id=\"dcu_control_lb_id\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_left\">10</property>\
                        <property name=\"margin_top\">10</property>\
                        <property name=\"margin_bottom\">10</property>\
                        <property name=\"label\" translatable=\"yes\">Mã trạm</property>\
                        <attributes>\
                          <attribute name=\"weight\" value=\"bold\"/>\
                          <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                        </attributes>\
                      </object>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkButtonBox\" id=\"buttonbox1\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"layout_style\">end</property>\
                    <child>\
                      <object class=\"GtkButton\" id=\"dcu_schedule_summit_button\">\
                        <property name=\"label\" translatable=\"yes\">Thiết lập</property>\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"dcu_manual_summit_button\">\
                        <property name=\"label\" translatable=\"yes\">Thiết lập</property>\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"relief\">half</property>\
                        <property name=\"xalign\">0.46000000834465027</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">False</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">4</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"box24\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkScrolledWindow\" id=\"scrolledwindow10\">\
                    <property name=\"width_request\">200</property>\
                    <property name=\"height_request\">200</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"hscrollbar_policy\">never</property>\
                    <property name=\"vscrollbar_policy\">never</property>\
                    <property name=\"shadow_type\">in</property>\
                    <child>\
                      <object class=\"GtkViewport\" id=\"viewport3\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkBox\" id=\"dcu_control_osm_map_box\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <placeholder/>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
  <object class=\"GtkDialog\" id=\"lcu_control_dialog\">\
    <property name=\"width_request\">380</property>\
    <property name=\"height_request\">400</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_control_ok\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close6\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box48\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"label52\">\
                <property name=\"height_request\">50</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Điều Khiển Đèn</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 16\"/>\
                  <attribute name=\"weight\" value=\"heavy\"/>\
                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkGrid\" id=\"grid1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"row_spacing\">5</property>\
                <property name=\"column_spacing\">5</property>\
                <child>\
                  <object class=\"GtkLabel\" id=\"lcu_control_label_id\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"height_request\">30</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">label</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 12\"/>\
                      <attribute name=\"weight\" value=\"heavy\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"lcu_control_combobox_mode\">\
                    <property name=\"width_request\">200</property>\
                    <property name=\"height_request\">30</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"has_tooltip\">True</property>\
                    <property name=\"tooltip_markup\" translatable=\"yes\">	</property>\
                    <property name=\"tooltip_text\" translatable=\"yes\">	</property>\
                    <items>\
                      <item translatable=\"yes\">Schedule Mode</item>\
                      <item translatable=\"yes\">Manual Mode</item>\
                    </items>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label53\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"height_request\">30</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Mã thiết bị điều khiển:</property>\
                    <property name=\"angle\">0.02</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label38\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"height_request\">30</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Loại đèn:</property>\
                    <property name=\"angle\">0.02</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label54\">\
                    <property name=\"width_request\">120</property>\
                    <property name=\"height_request\">30</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Chế độ hoạt động:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">2</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkLabel\" id=\"lcu_control_label_lightname\">\
                    <property name=\"width_request\">150</property>\
                    <property name=\"height_request\">30</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">label</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 10\"/>\
                      <attribute name=\"foreground\" value=\"#000000000000\"/>\
                    </attributes>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"lcu_control_manual_mode_frame\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">10</property>\
                <property name=\"border_width\">5</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment1\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkGrid\" id=\"grid10\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"border_width\">5</property>\
                        <property name=\"row_spacing\">5</property>\
                        <property name=\"column_spacing\">5</property>\
                        <child>\
                          <object class=\"GtkLabel\" id=\"label57\">\
                            <property name=\"width_request\">120</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"xalign\">0</property>\
                            <property name=\"label\" translatable=\"yes\">Bật/ tắt:</property>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">0</property>\
                            <property name=\"top_attach\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkLabel\" id=\"label58\">\
                            <property name=\"width_request\">120</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"xalign\">0</property>\
                            <property name=\"label\" translatable=\"yes\">Cấp độ sáng:</property>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">0</property>\
                            <property name=\"top_attach\">1</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkSwitch\" id=\"lcu_control_switch_on_off\">\
                            <property name=\"use_action_appearance\">False</property>\
                            <property name=\"width_request\">200</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">1</property>\
                            <property name=\"top_attach\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\" id=\"lcu_control_scale_box_lightlevel\">\
                            <property name=\"width_request\">200</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <object class=\"GtkScale\" id=\"lcu_control_scale_level\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"adjustment\">lcu_brightness_adjustment</property>\
                                <property name=\"fill_level\">10</property>\
                                <property name=\"round_digits\">0</property>\
                                <property name=\"digits\">0</property>\
                                <property name=\"value_pos\">right</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">1</property>\
                            <property name=\"top_attach\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label56\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Điểu khiển trực tiếp:</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 12\"/>\
                      <attribute name=\"weight\" value=\"heavy\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkCheckButton\" id=\"lcu_control_istemp_checkbutton\">\
                <property name=\"label\" translatable=\"yes\">Phiên làm việc hiện tại</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">False</property>\
                <property name=\"margin_left\">20</property>\
                <property name=\"margin_top\">5</property>\
                <property name=\"margin_bottom\">5</property>\
                <property name=\"xalign\">0</property>\
                <property name=\"draw_indicator\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">4</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">lcu_control_ok</action-widget>\
      <action-widget response=\"-7\">lcu_close6</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"schedule_item_new_dialog\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"title\" translatable=\"yes\">Chương trình hoạt động ngày cho đèn</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"default_height\">550</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox24\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog_action_area_schedule\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_top\">5</property>\
            <property name=\"margin_bottom\">5</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_update5\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close10\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box18\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"lb_schedule_tittle\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">10</property>\
                <property name=\"margin_bottom\">10</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 16\"/>\
                  <attribute name=\"weight\" value=\"bold\"/>\
                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"box26\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkGrid\" id=\"grid18\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">10</property>\
                    <property name=\"margin_bottom\">10</property>\
                    <property name=\"row_spacing\">5</property>\
                    <property name=\"column_spacing\">5</property>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label91\">\
                        <property name=\"width_request\">100</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_top\">5</property>\
                        <property name=\"margin_bottom\">5</property>\
                        <property name=\"label\" translatable=\"yes\">Tên:</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">0</property>\
                        <property name=\"top_attach\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkEntry\" id=\"schedule_item_name_entry\">\
                        <property name=\"width_request\">300</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">1</property>\
                        <property name=\"top_attach\">0</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\" id=\"box81\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label96\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_top\">10</property>\
                        <property name=\"margin_bottom\">10</property>\
                        <property name=\"label\" translatable=\"yes\">Thông tin hoạt động</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkScrolledWindow\" id=\"scrolledwindow1\">\
                        <property name=\"width_request\">400</property>\
                        <property name=\"height_request\">200</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"shadow_type\">in</property>\
                        <child>\
                          <object class=\"GtkTreeView\" id=\"schedule_item_content_treeview\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"rules_hint\">True</property>\
                            <child internal-child=\"selection\">\
                              <object class=\"GtkTreeSelection\" id=\"treeview-selection35\"/>\
                            </child>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box82\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkButtonBox\" id=\"buttonbox4\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"border_width\">4</property>\
                            <property name=\"spacing\">2</property>\
                            <property name=\"layout_style\">end</property>\
                            <child>\
                              <object class=\"GtkButton\" id=\"btn_item_add\">\
                                <property name=\"label\" translatable=\"yes\">Mới</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">True</property>\
                                <property name=\"image\">image_add</property>\
                                <property name=\"always_show_image\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">True</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkButton\" id=\"btn_item_edit\">\
                                <property name=\"label\" translatable=\"yes\">Sửa</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">True</property>\
                                <property name=\"image\">image_edit</property>\
                                <property name=\"always_show_image\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">True</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkButton\" id=\"btn_item_remove\">\
                                <property name=\"label\" translatable=\"yes\">Xóa</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">True</property>\
                                <property name=\"image\">image_remove</property>\
                                <property name=\"always_show_image\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">True</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">2</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">2</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkFrame\" id=\"frame_config_schedule\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label_xalign\">0</property>\
                        <property name=\"shadow_type\">in</property>\
                        <child>\
                          <object class=\"GtkAlignment\" id=\"alignment20\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"left_padding\">12</property>\
                            <child>\
                              <object class=\"GtkGrid\" id=\"grid19\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"margin_bottom\">5</property>\
                                <property name=\"row_spacing\">3</property>\
                                <child>\
                                  <object class=\"GtkLabel\" id=\"label93\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"xalign\">0</property>\
                                    <property name=\"label\" translatable=\"yes\">Thời gian tắt đèn:</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"left_attach\">0</property>\
                                    <property name=\"top_attach\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkLabel\" id=\"label94\">\
                                    <property name=\"width_request\">125</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"xalign\">0</property>\
                                    <property name=\"label\" translatable=\"yes\">Thời gian mở đèn:</property>\
                                    <property name=\"ellipsize\">start</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"left_attach\">0</property>\
                                    <property name=\"top_attach\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkLabel\" id=\"label95\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"xalign\">0</property>\
                                    <property name=\"label\" translatable=\"yes\">Độ sáng của đèn:</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"left_attach\">0</property>\
                                    <property name=\"top_attach\">2</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"schedule_item_level_box\">\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"orientation\">vertical</property>\
                                    <child>\
                                      <object class=\"GtkFixed\" id=\"fixed3\">\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <child>\
                                          <object class=\"GtkBox\" id=\"box55\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <child>\
                                              <object class=\"GtkScale\" id=\"scale1\">\
                                                <property name=\"width_request\">200</property>\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">True</property>\
                                                <property name=\"adjustment\">lcu_brightness_adjustment</property>\
                                                <property name=\"fill_level\">100</property>\
                                                <property name=\"round_digits\">0</property>\
                                                <property name=\"digits\">0</property>\
                                                <property name=\"value_pos\">left</property>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">0</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkButton\" id=\"btn_item_accept\">\
                                                <property name=\"label\" translatable=\"yes\">Hoàn thành</property>\
                                                <property name=\"use_action_appearance\">False</property>\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">True</property>\
                                                <property name=\"receives_default\">True</property>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"left_attach\">1</property>\
                                    <property name=\"top_attach\">2</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkFixed\" id=\"fixed2\">\
                                    <property name=\"width_request\">32</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <child>\
                                      <object class=\"GtkBox\" id=\"box62\">\
                                        <property name=\"width_request\">100</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <property name=\"halign\">start</property>\
                                        <property name=\"spacing\">4</property>\
                                        <child>\
                                          <object class=\"GtkComboBoxText\" id=\"cbb_startHour\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"has_entry\">True</property>\
                                            <child internal-child=\"entry\">\
                                              <object class=\"GtkEntry\" id=\"comboboxtext-entry9\">\
                                                <property name=\"can_focus\">True</property>\
                                                <property name=\"max_length\">2</property>\
                                                <property name=\"width_chars\">2</property>\
                                                <property name=\"xalign\">1</property>\
                                              </object>\
                                            </child>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">0</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkLabel\" id=\"label43\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label\" translatable=\"yes\">Giờ</property>\
                                            <property name=\"max_width_chars\">3</property>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">1</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkComboBoxText\" id=\"cbb_startMinute\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"has_entry\">True</property>\
                                            <child internal-child=\"entry\">\
                                              <object class=\"GtkEntry\" id=\"comboboxtext-entry10\">\
                                                <property name=\"can_focus\">True</property>\
                                                <property name=\"max_length\">2</property>\
                                                <property name=\"width_chars\">2</property>\
                                                <property name=\"xalign\">1</property>\
                                              </object>\
                                            </child>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">2</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkLabel\" id=\"label71\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"label\" translatable=\"yes\">Phút</property>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">3</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <object class=\"GtkImage\" id=\"image_startTime\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"tooltip_text\" translatable=\"yes\">Thời gian không phù hợp</property>\
                                            <property name=\"xalign\">0.80000001192092896</property>\
                                            <property name=\"stock\">gtk-dialog-warning</property>\
                                          </object>\
                                          <packing>\
                                            <property name=\"expand\">False</property>\
                                            <property name=\"fill\">True</property>\
                                            <property name=\"position\">4</property>\
                                          </packing>\
                                        </child>\
                                        <child>\
                                          <placeholder/>\
                                        </child>\
                                      </object>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"left_attach\">1</property>\
                                    <property name=\"top_attach\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkBox\" id=\"box63\">\
                                    <property name=\"width_request\">100</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">False</property>\
                                    <property name=\"halign\">start</property>\
                                    <property name=\"orientation\">vertical</property>\
                                    <child>\
                                      <object class=\"GtkFixed\" id=\"fixed1\">\
                                        <property name=\"width_request\">32</property>\
                                        <property name=\"visible\">True</property>\
                                        <property name=\"can_focus\">False</property>\
                                        <child>\
                                          <object class=\"GtkBox\" id=\"box71\">\
                                            <property name=\"visible\">True</property>\
                                            <property name=\"can_focus\">False</property>\
                                            <property name=\"spacing\">4</property>\
                                            <child>\
                                              <object class=\"GtkComboBoxText\" id=\"cbb_endHour\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"has_entry\">True</property>\
                                                <child internal-child=\"entry\">\
                                                  <object class=\"GtkEntry\" id=\"comboboxtext-entry11\">\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"max_length\">2</property>\
                                                    <property name=\"width_chars\">2</property>\
                                                    <property name=\"xalign\">1</property>\
                                                  </object>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">0</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkLabel\" id=\"label40\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"label\" translatable=\"yes\">Giờ</property>\
                                                <property name=\"max_width_chars\">3</property>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">1</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkComboBoxText\" id=\"cbb_endMinute\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"has_entry\">True</property>\
                                                <child internal-child=\"entry\">\
                                                  <object class=\"GtkEntry\" id=\"comboboxtext-entry12\">\
                                                    <property name=\"can_focus\">True</property>\
                                                    <property name=\"max_length\">2</property>\
                                                    <property name=\"width_chars\">2</property>\
                                                    <property name=\"xalign\">1</property>\
                                                  </object>\
                                                </child>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">2</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkLabel\" id=\"label42\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"label\" translatable=\"yes\">Phút</property>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">3</property>\
                                              </packing>\
                                            </child>\
                                            <child>\
                                              <object class=\"GtkImage\" id=\"image_endTime\">\
                                                <property name=\"visible\">True</property>\
                                                <property name=\"can_focus\">False</property>\
                                                <property name=\"tooltip_text\" translatable=\"yes\">Thời gian không phù hợp</property>\
                                                <property name=\"xalign\">0.80000001192092896</property>\
                                                <property name=\"stock\">gtk-dialog-warning</property>\
                                              </object>\
                                              <packing>\
                                                <property name=\"expand\">False</property>\
                                                <property name=\"fill\">True</property>\
                                                <property name=\"position\">4</property>\
                                              </packing>\
                                            </child>\
                                          </object>\
                                        </child>\
                                      </object>\
                                      <packing>\
                                        <property name=\"expand\">False</property>\
                                        <property name=\"fill\">True</property>\
                                        <property name=\"position\">0</property>\
                                      </packing>\
                                    </child>\
                                  </object>\
                                  <packing>\
                                    <property name=\"left_attach\">1</property>\
                                    <property name=\"top_attach\">1</property>\
                                  </packing>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                        </child>\
                        <child type=\"label\">\
                          <object class=\"GtkLabel\" id=\"label36\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"label\" translatable=\"yes\">Cấu hình</property>\
                          </object>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">3</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">lcu_update5</action-widget>\
      <action-widget response=\"-7\">lcu_close10</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"lcu_slope_datetime_dialog\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox34\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area36\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_top\">10</property>\
            <property name=\"margin_bottom\">10</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_update9\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close16\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box50\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkFrame\" id=\"frame10\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"border_width\">5</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment23\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_bottom\">1</property>\
                    <property name=\"left_padding\">10</property>\
                    <child>\
                      <object class=\"GtkButton\" id=\"slope_btn_start_time\">\
                        <property name=\"label\" translatable=\"yes\">button</property>\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"margin_bottom\">8</property>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label167\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Thời gian bắt đầu</property>\
                    <attributes>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"frame13\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"border_width\">5</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment24\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"left_padding\">10</property>\
                    <child>\
                      <object class=\"GtkButton\" id=\"slope_btn_end_time\">\
                        <property name=\"label\" translatable=\"yes\">button</property>\
                        <property name=\"use_action_appearance\">False</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"margin_bottom\">8</property>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label168\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Thời gian kết thúc</property>\
                    <attributes>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkCheckButton\" id=\"autoload_time\">\
                <property name=\"label\" translatable=\"yes\">Lưu thời gian lựa chọn làm mặc định</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">False</property>\
                <property name=\"xalign\">0</property>\
                <property name=\"draw_indicator\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">4</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">lcu_update9</action-widget>\
      <action-widget response=\"-6\">lcu_close16</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"dialog_date_n_time\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"title\" translatable=\"yes\">Chọn thời gian</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"modal\">True</property>\
    <property name=\"window_position\">center</property>\
    <property name=\"destroy_with_parent\">True</property>\
    <property name=\"type_hint\">dialog</property>\
    <property name=\"transient_for\">lcu_slope_datetime_dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox36\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area34\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <placeholder/>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"button5\">\
                <property name=\"label\" translatable=\"yes\">Thoát</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box88\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"border_width\">5</property>\
            <property name=\"spacing\">3</property>\
            <child>\
              <object class=\"GtkCalendar\" id=\"calendar_select\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"year\">2016</property>\
                <property name=\"month\">11</property>\
                <property name=\"day\">6</property>\
                <property name=\"show_details\">False</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFixed\" id=\"fixed4\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkGrid\" id=\"grid24\">\
                    <property name=\"width_request\">100</property>\
                    <property name=\"height_request\">80</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"row_spacing\">6</property>\
                    <property name=\"column_spacing\">3</property>\
                    <child>\
                      <object class=\"GtkSpinButton\" id=\"spinbutton_hour\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"tooltip_text\" translatable=\"yes\">Chọn giờ</property>\
                        <property name=\"max_length\">2</property>\
                        <property name=\"xalign\">0.5</property>\
                        <property name=\"adjustment\">adjustment_hh</property>\
                        <property name=\"numeric\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">0</property>\
                        <property name=\"top_attach\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label164\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label\" translatable=\"yes\">Giờ</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">0</property>\
                        <property name=\"top_attach\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label165\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label\" translatable=\"yes\">Phút</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">1</property>\
                        <property name=\"top_attach\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label166\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"label\" translatable=\"yes\">Giây</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">2</property>\
                        <property name=\"top_attach\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkSpinButton\" id=\"spinbutton_minute\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"tooltip_text\" translatable=\"yes\">Chọn phút</property>\
                        <property name=\"max_length\">2</property>\
                        <property name=\"xalign\">0.5</property>\
                        <property name=\"adjustment\">adjustment_mm</property>\
                        <property name=\"numeric\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">1</property>\
                        <property name=\"top_attach\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkSpinButton\" id=\"spinbutton_second\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"tooltip_text\" translatable=\"yes\">Chọn giây</property>\
                        <property name=\"max_length\">2</property>\
                        <property name=\"xalign\">0.5</property>\
                        <property name=\"adjustment\">adjustment_ss</property>\
                        <property name=\"numeric\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">2</property>\
                        <property name=\"top_attach\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"y\">15</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">button5</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"list_schedule_dialog_change\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox25\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area25\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_update3\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close9\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box4\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_left\">10</property>\
            <property name=\"margin_right\">10</property>\
            <property name=\"margin_top\">10</property>\
            <property name=\"margin_bottom\">10</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"label19\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">10</property>\
                <property name=\"margin_bottom\">10</property>\
                <property name=\"label\" translatable=\"yes\">Chọn lập lịch:</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkGrid\" id=\"grid17\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label20\">\
                    <property name=\"width_request\">90</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">9</property>\
                    <property name=\"margin_bottom\">10</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"label\" translatable=\"yes\">Tên lập lịch:</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">0</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"list_schedule_combobox_change\">\
                    <property name=\"width_request\">200</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"margin_bottom\">5</property>\
                    <property name=\"border_width\">5</property>\
                  </object>\
                  <packing>\
                    <property name=\"left_attach\">1</property>\
                    <property name=\"top_attach\">0</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"2\">lcu_update3</action-widget>\
      <action-widget response=\"1\">lcu_close9</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"login_dialog\">\
    <property name=\"width_request\">300</property>\
    <property name=\"height_request\">200</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"border_width\">5</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"window_position\">center</property>\
    <property name=\"type_hint\">dialog</property>\
    <property name=\"deletable\">False</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox10\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area10\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_top\">10</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"login_commit\">\
                <property name=\"label\" translatable=\"yes\">Xác Nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"login_cancel\">\
                <property name=\"label\" translatable=\"yes\">Hủy</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box10\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"label11\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">10</property>\
                <property name=\"margin_right\">10</property>\
                <property name=\"margin_top\">10</property>\
                <property name=\"margin_bottom\">10</property>\
                <property name=\"xalign\">0.43999999761581421</property>\
                <property name=\"label\" translatable=\"yes\">HỆ THỐNG QUẢN LÝ ĐÈN ĐƯỜNG THÔNG MINH</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 16\"/>\
                  <attribute name=\"weight\" value=\"bold\"/>\
                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"label12\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Đăng Nhập Vào Hệ Thống</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 12\"/>\
                  <attribute name=\"foreground\" value=\"#34346565a4a4\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"login_label_error\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"box11\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"border_width\">10</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkGrid\" id=\"grid4\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"row_spacing\">2</property>\
                    <property name=\"column_spacing\">5</property>\
                    <child>\
                      <object class=\"GtkEntry\" id=\"dialog_login_username\">\
                        <property name=\"width_request\">300</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">1</property>\
                        <property name=\"top_attach\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkEntry\" id=\"dialog_login_password\">\
                        <property name=\"width_request\">300</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">1</property>\
                        <property name=\"top_attach\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label1\">\
                        <property name=\"width_request\">100</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"xalign\">0</property>\
                        <property name=\"label\" translatable=\"yes\">Tên tài khoản:</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">0</property>\
                        <property name=\"top_attach\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkLabel\" id=\"label3\">\
                        <property name=\"width_request\">100</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"xalign\">0</property>\
                        <property name=\"label\" translatable=\"yes\">Mật khẩu:</property>\
                      </object>\
                      <packing>\
                        <property name=\"left_attach\">0</property>\
                        <property name=\"top_attach\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkCheckButton\" id=\"remember_login_checkbutton\">\
                    <property name=\"label\" translatable=\"yes\">Ghi nhớ đăng nhập</property>\
                    <property name=\"use_action_appearance\">False</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">False</property>\
                    <property name=\"margin_left\">102</property>\
                    <property name=\"margin_top\">3</property>\
                    <property name=\"xalign\">0</property>\
                    <property name=\"draw_indicator\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"pack_type\">end</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkExpander\" id=\"login_custom_expander\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <child>\
                  <object class=\"GtkBox\" id=\"box107\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkGrid\" id=\"grid14\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_top\">5</property>\
                        <property name=\"row_spacing\">5</property>\
                        <property name=\"column_spacing\">5</property>\
                        <property name=\"row_homogeneous\">True</property>\
                        <child>\
                          <object class=\"GtkLabel\" id=\"label106\">\
                            <property name=\"width_request\">100</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"xalign\">0.10000000149011612</property>\
                            <property name=\"label\" translatable=\"yes\">Địa chỉ Server:</property>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">0</property>\
                            <property name=\"top_attach\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkLabel\" id=\"label107\">\
                            <property name=\"width_request\">100</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"xalign\">0.10000000149011612</property>\
                            <property name=\"label\" translatable=\"yes\">Cổng kết nối:</property>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">0</property>\
                            <property name=\"top_attach\">1</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkEntry\" id=\"login_server_url_entry\">\
                            <property name=\"width_request\">100</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"hexpand\">True</property>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">1</property>\
                            <property name=\"top_attach\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkEntry\" id=\"login_server_port_entry\">\
                            <property name=\"width_request\">100</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"hexpand\">True</property>\
                          </object>\
                          <packing>\
                            <property name=\"left_attach\">1</property>\
                            <property name=\"top_attach\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label105\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Cấu hình nâng cao</property>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">4</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-5\">login_commit</action-widget>\
      <action-widget response=\"-7\">login_cancel</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"notification_dlg\">\
    <property name=\"name\">notification_dlg</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"resizable\">False</property>\
    <property name=\"window_position\">center-always</property>\
    <property name=\"type_hint\">dialog</property>\
    <property name=\"decorated\">False</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox18\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area18\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"button7\">\
                <property name=\"label\" translatable=\"yes\">Lưu</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <property name=\"no_show_all\">True</property>\
                <property name=\"relief\">none</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"button6\">\
                <property name=\"label\" translatable=\"yes\">Xóa hết</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"notification_btn_quit1\">\
                <property name=\"label\" translatable=\"yes\">Thoát</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box12\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"border_width\">5</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkBox\" id=\"box28\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <child>\
                  <object class=\"GtkLabel\" id=\"label4\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">30</property>\
                    <property name=\"margin_top\">10</property>\
                    <property name=\"label\" translatable=\"yes\">Thông báo</property>\
                    <attributes>\
                      <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 20\"/>\
                      <attribute name=\"weight\" value=\"heavy\"/>\
                    </attributes>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkButton\" id=\"notification_btn_quit\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"receives_default\">True</property>\
                    <property name=\"margin_bottom\">12</property>\
                    <property name=\"relief\">none</property>\
                    <child>\
                      <object class=\"GtkImage\" id=\"image1\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"xalign\">0.47999998927116394</property>\
                        <property name=\"stock\">gtk-close</property>\
                        <property name=\"icon_size\">2</property>\
                      </object>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkLabel\" id=\"label5\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">5</property>\
                <property name=\"margin_bottom\">3</property>\
                <property name=\"label\" translatable=\"yes\">(Nhấp đôi vào để đọc, sau khi đọc thông báo sẽ tự động xóa trong danh sách)</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"&lt;Enter Value&gt; 8\"/>\
                  <attribute name=\"foreground\" value=\"#efef29292929\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkScrolledWindow\" id=\"scrolledwindow9\">\
                <property name=\"height_request\">200</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkTreeView\" id=\"notification_view\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"rules_hint\">True</property>\
                    <property name=\"enable_grid_lines\">both</property>\
                    <child internal-child=\"selection\">\
                      <object class=\"GtkTreeSelection\" id=\"treeview-selection26\"/>\
                    </child>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"-2\">button6</action-widget>\
      <action-widget response=\"-5\">notification_btn_quit1</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"spl_admin_zone_own_choose_dialog\">\
    <property name=\"width_request\">500</property>\
    <property name=\"height_request\">300</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox21\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area21\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_update10\">\
                <property name=\"label\" translatable=\"yes\">Xác nhận</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close17\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box32\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkScrolledWindow\" id=\"scrolledwindow6\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"margin_top\">10</property>\
                <property name=\"margin_bottom\">10</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkTreeView\" id=\"spl_admin_zone_own_choose_treeview\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <child internal-child=\"selection\">\
                      <object class=\"GtkTreeSelection\" id=\"treeview-selection41\"/>\
                    </child>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"2\">lcu_update10</action-widget>\
      <action-widget response=\"1\">lcu_close17</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkDialog\" id=\"user_information_dialog\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"window_position\">center</property>\
    <property name=\"type_hint\">dialog</property>\
    <child internal-child=\"vbox\">\
      <object class=\"GtkBox\" id=\"dialog-vbox31\">\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <property name=\"spacing\">2</property>\
        <child internal-child=\"action_area\">\
          <object class=\"GtkButtonBox\" id=\"dialog-action_area31\">\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_left\">10</property>\
            <property name=\"margin_right\">10</property>\
            <property name=\"margin_top\">10</property>\
            <property name=\"margin_bottom\">10</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_update6\">\
                <property name=\"label\" translatable=\"yes\">Cập nhật</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"lcu_close12\">\
                <property name=\"label\" translatable=\"yes\">Đóng</property>\
                <property name=\"use_action_appearance\">False</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">False</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\" id=\"box95\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_top\">20</property>\
            <property name=\"border_width\">5</property>\
            <property name=\"orientation\">vertical</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"lb_dialog_lcu_name1\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_bottom\">20</property>\
                <property name=\"label\" translatable=\"yes\">THÔNG TIN TÀI KHOẢN</property>\
                <property name=\"angle\">0.11</property>\
                <attributes>\
                  <attribute name=\"font-desc\" value=\"Bitstream Vera Serif 16\"/>\
                  <attribute name=\"weight\" value=\"bold\"/>\
                  <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                </attributes>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"aaaa\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment10\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box104\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid21\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_bottom\">2</property>\
                            <property name=\"row_spacing\">5</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label128\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Mật khẩu:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label130\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Tên đăng nhập:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"user_info_password_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"user_info_account_label\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">label</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"user_info_retype_passwd_new_grid\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"user_info_password_2_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label131\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Nhập lại mật khẩu:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label127\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Thông tin cơ bản</property>\
                    <attributes>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"frame3\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_top\">20</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">in</property>\
                <child>\
                  <object class=\"GtkAlignment\" id=\"alignment11\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\" id=\"box105\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"orientation\">vertical</property>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid26\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"row_spacing\">2</property>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label133\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Số điện thoại:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkLabel\" id=\"label134\">\
                                <property name=\"width_request\">150</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"label\" translatable=\"yes\">Địa chỉ Email:</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"user_info_phone_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkEntry\" id=\"user_info_email_entry\">\
                                <property name=\"width_request\">300</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">1</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkGrid\" id=\"grid25\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_top\">20</property>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"user_enable_notify_sms_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Nhận thông tin cảnh báo bằng sms gửi đến số điện thoại đã cung cấp.</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"width_request\">250</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"margin_top\">3</property>\
                                <property name=\"margin_bottom\">3</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkCheckButton\" id=\"user_enable_notify_email_checkbutton\">\
                                <property name=\"label\" translatable=\"yes\">Nhận thông tin cảnh báo thông qua email đã cung cấp.</property>\
                                <property name=\"use_action_appearance\">False</property>\
                                <property name=\"width_request\">250</property>\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"receives_default\">False</property>\
                                <property name=\"margin_top\">3</property>\
                                <property name=\"margin_bottom\">3</property>\
                                <property name=\"xalign\">0</property>\
                                <property name=\"draw_indicator\">True</property>\
                              </object>\
                              <packing>\
                                <property name=\"left_attach\">0</property>\
                                <property name=\"top_attach\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\" id=\"label132\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Thông tin cấu hình</property>\
                    <attributes>\
                      <attribute name=\"weight\" value=\"bold\"/>\
                      <attribute name=\"foreground\" value=\"#20204a4a8787\"/>\
                    </attributes>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
    <action-widgets>\
      <action-widget response=\"2\">lcu_update6</action-widget>\
      <action-widget response=\"1\">lcu_close12</action-widget>\
    </action-widgets>\
  </object>\
  <object class=\"GtkWindow\" id=\"waiting_window\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"opacity\">0.5</property>\
    <property name=\"modal\">True</property>\
    <property name=\"window_position\">center-always</property>\
    <property name=\"decorated\">False</property>\
    <child>\
      <placeholder/>\
    </child>\
  </object>\
</interface> ";
