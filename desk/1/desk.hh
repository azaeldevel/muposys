
#ifndef OCTETOS_MUPOSYS_DESK_V1_HH
#define OCTETOS_MUPOSYS_DESK_V1_HH

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
#include <glibmm/i18n.h>
#include <gtkmm.h>

#include <muposys/core/1/core.hh>

namespace oct::mps::v1
{
    class Saling : public Gtk::Box
    {
    public:
        class Model : public Gtk::TreeModel::ColumnRecord
        {
        public:
            Model();

            Gtk::TreeModelColumn<Glib::ustring> number;
            Gtk::TreeModelColumn<unsigned long> amount;
            Gtk::TreeModelColumn<double> cost;
            Gtk::TreeModelColumn<double> total;
        };

    public:
        Saling();
        Saling(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);
        Saling(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&,Crud);
        inline void init_controls(const Glib::RefPtr<Gtk::Builder>& builder);

    private:
        void on_row_activated(const Gtk::TreeModel::Path& , Gtk::TreeViewColumn*);
        bool keypress(GdkEventKey* key_event);

        void on_row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);
        void on_cell_editing_started(Gtk::CellEditable* 	editable, const Glib::ustring& 	path);
        void on_cell_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
        void on_column_editing_number(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
        void searching();

    private:
        Gtk::TreeView *table;
        Model model;
        Glib::RefPtr<Gtk::TreeStore> table_model;
        Crud crud;
        Gtk::TreeModel::Path path_actived;
        Gtk::CellRendererText* cellrender_number;
        Gtk::TreeViewColumn* col_number;
        Gtk::Entry* inSearch;
        std::string strsearch;
    };

    class Login : public Gtk::Dialog
    {
    public:
        Login(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);

    protected:
        void on_bt_Accept_clicked();
        void on_bt_Cancel_clicked();
        void on_response(int);

    private:
        Gtk::Entry *inUser,*inPassword;
        Gtk::Button *btAccept,*btCancel;
        Gtk::InfoBar* infoLogin;
        User user;

    private:
      inline void init_data();
      inline void init_controls(const Glib::RefPtr<Gtk::Builder>& builder);
      bool check(User&);
    };

    class Application : public Gtk::Window
    {
    public:
        enum class Layout
        {
            none,
            client_only,
            compressed,//toolbar y area de cliente
            sandwich,//area cliente en 3 sub-areas
            glade,
        };
        struct Configuration
        {
            Layout layout;
            bool main_menu;
            bool status_bar;
            Glib::ustring title,subtitle;
            int width,height;

            Configuration();
        };

    public:
      Application();
      Application(const Configuration& config);
      Application(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);

      virtual void check_session();

      Gtk::MenuBar& get_menus();
      Gtk::Box& get_toolpane();
      Gtk::Stack& get_stack();

    protected:

    private:
        Configuration config;

        Gtk::HeaderBar *header;
        Gtk::Box *boxSlices,*boxToolPane;
        Gtk::MenuBar *menu;
        Gtk::Stack *stack;
        Gtk::Statusbar *status;
        Login *login;

    private:
      inline void init_data();
      inline void init_controls(const Glib::RefPtr<Gtk::Builder>& builder);

    };

}

#endif
