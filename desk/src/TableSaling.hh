
#ifndef MUPOSYS_DESK_TABLES_SALEN_HH
#define MUPOSYS_DESK_TABLES_SALEN_HH

#if __linux__
    #include <muposys/core/muposysdb.hpp>
#elif MSYS2
    #include <muposys/core/bin/muposysdb.hpp>
#else
    #error "Plataforma desconocida."
#endif

namespace mps
{


class TableSaling : public Gtk::VBox
{
public:
	TableSaling();
	void init();
	virtual ~TableSaling();

    void set_info(Gtk::Notebook& parent,int page_index);

protected:
	Connector connDB;
	bool connDB_flag;

	void row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);

	void treeviewcolumn_validated_on_cell_data_number(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_number(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text);

	//void treeviewcolumn_validated_on_cell_data_quantity(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	//void cellrenderer_validated_on_editing_started_quantity(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text);

	//bool on_key_press_event(GdkEventKey* key_event);
	bool on_quantity_key_press_event(GdkEventKey* key_event);

	float total()const;
	void newrow();
	virtual void clear();
    void mark_unsave();

#ifdef MUPOSYS_DESK_ENABLE_TDD
	void on_save_clicked();
    virtual void save();
#else
    virtual void save() = 0;
#endif
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns();

		Gtk::TreeModelColumn<int> item;
		Gtk::TreeModelColumn<int> quantity;
		Gtk::TreeModelColumn<Glib::ustring> presentation;
		Gtk::TreeModelColumn<Glib::ustring> number;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<float> cost_unit;
		Gtk::TreeModelColumn<float> amount;
	};

	ModelColumns columns;
	Glib::RefPtr<Gtk::ListStore> tree_model;
	bool saved;
	Gtk::Notebook* notebook;
    int notebook_page_index;

	Gtk::TreeView table;
	Gtk::Button btSave;
	Gtk::Label lbTotal, lbTotalAmount;
	Gtk::HBox boxTotal;
	Gtk::VBox boxFloor,boxAditional;
	Gtk::HSeparator separator;
};


}

#endif
