
#ifndef MUPOSYS_DESK_TABLES_SALEN_HH
#define MUPOSYS_DESK_TABLES_SALEN_HH

/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 *
 * muposys is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * muposys is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm.h>

#if __linux__
    #include <muposys/cave/maria.hh>
    #include <muposys/core/core.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <cave/src/maria.hh>
    #include <muposys/core/src/core.hh>
#else
    #error "Plataforma desconocida."
#endif

namespace mps::v1
{


struct CatalogItem
{
    long id;
    std::string number,brief,presentation;
    short station;
    float value;

    CatalogItem() = default;
    CatalogItem(const char** r);
};

struct CatalogItem_Save
{
    long id;
    short type;

    CatalogItem_Save() = default;
    CatalogItem_Save(const char** r);
    CatalogItem_Save(long id,cave_current::OCTETOS_CAVE_DRIVER::Connection& connDB);
};
struct Sale
{
    long id,operation,stock,item,amount;

    Sale() = default;
    Sale(const char** r);
};

struct Stock
{
    long id;
    std::string brief;

    Stock() = default;
    Stock(const char** r);
    Stock(long id);
};


struct Stocking
{

    Stocking() = default;
    Stocking(const char** r);
    Stocking(long id);
};

struct Operation
{
    long id;
    Operation() = default;
    Operation(const char** r);

    static std::string fields();
};

struct Progress
{

    Progress() = default;
    Progress(const char** r);
};

class TableSaling : public Gtk::Box
{
public:
	TableSaling();
	TableSaling(long order);
	TableSaling(long order,mps::Crud);
	void init();
	virtual ~TableSaling();

    void set_info(Gtk::Notebook& parent,int page_index);

protected:

	cave_current::OCTETOS_CAVE_DRIVER::Connection connDB;
	bool connDB_flag;

	void row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);

	void treeviewcolumn_validated_on_cell_data_number(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_number(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text);

	//void treeviewcolumn_validated_on_cell_data_quantity(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	//void cellrenderer_validated_on_editing_started_quantity(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text);

	//bool on_key_press_event(GdkEventKey* key_event);
	//bool on_quantity_key_press_event(GdkEventKey* key_event);

	float total()const;
	void newrow();
	virtual void clear();
    void mark_unsave();

    virtual void download(long order);

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
	Gtk::Box boxTotal;
	Gtk::Box boxFloor,boxAditional;
	Gtk::Separator separator;
	Crud crud;
	long order;
};


}

#endif
