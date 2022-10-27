
#ifndef MUPOSYS_DESK_TABLES_SALEN_HH
#define MUPOSYS_DESK_TABLES_SALEN_HH

namespace mps
{


class TableSaling : public Gtk::VBox
{	
public:
	TableSaling();
	void init();
	virtual ~TableSaling();
	
	void set_page(Gtk::Widget&);
	
protected:
	Connector connDB;
	bool connDB_flag;
	
	void row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);
	
	void treeviewcolumn_validated_on_cell_data_number(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_number(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	void treeviewcolumn_validated_on_cell_data_quantity(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_quantity(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	bool on_key_press_event(GdkEventKey* key_event);
	bool on_quantity_key_press_event(GdkEventKey* key_event);
	
	void on_save_clicked();
	
	float total()const;
	
	void newrow();
	
	void clear();
	
#ifdef MUPOSYS_DESK_ENABLE_TDD
    virtual void save();
#else
    virtual void save() = 0;
#endif
    
private:
	
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns();
		//Gtk::TreeModelColumn<unsigned int> id;		
		Gtk::TreeModelColumn<int> item;
		Gtk::TreeModelColumn<int> quantity;
		//Gtk::TreeModelColumn<bool> quantity_valid;
		Gtk::TreeModelColumn<Glib::ustring> presentation;
		Gtk::TreeModelColumn<Glib::ustring> number;
		//Gtk::TreeModelColumn<bool> number_validated;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<float> cost_unit;
		Gtk::TreeModelColumn<float> amount;
		//Gtk::TreeModelColumn<bool> amount_valid;
	};
	
	ModelColumns columns;
	Glib::RefPtr<Gtk::ListStore> tree_model;
	Gtk::TreeView table;
	Gtk::Button btSave;
	Gtk::Label lbTotal,lbTotalAmount;
	Gtk::ButtonBox boxTotal;
	Gtk::ButtonBox boxFloor;
	bool saved;
	Gtk::Widget* page;
};


}

#endif
