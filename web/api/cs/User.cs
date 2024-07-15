using MySql.Data.MySqlClient;
using Newtonsoft.Json;
using System.Data;

namespace cs
{
    public class User
    {
        public int id { get; set; }
        public int person { get; set; }
        public string? name { get; set; }

        public string to_json()
        {
            return JsonConvert.SerializeObject(this);
        }
    }

    public interface IUserService
    {

        List<User> GetUsers();

        User GetUser(int id);
    }
    public class UserService : IUserService
    {
        private readonly List<User> list;
        public UserService()
        {
            list = new List<User>();
            load();
        }
        public List<User> GetUsers()
        {
            return list;
        }

        public User GetUser(int id)
        {
            var user = list.FirstOrDefault(x => x.id == id);
            if (user == null) return new User() { id = 0,person = 0, name = "'none'" };
            return user;
        }

        public void load()
        {
            string sql = " SELECT * FROM User";
            MySqlConnection con = new MySqlConnection("host=localhost;user=develop;password=123456;database=muposys-dev;");
            MySqlCommand cmd = new MySqlCommand(sql, con);
            con.Open();
            MySqlDataReader reader = cmd.ExecuteReader();
            User u;
            while (reader.Read())
            {
                u = new User();
                u.id = reader.GetInt32("id");
                u.person = reader.GetInt32("person");
                u.name = reader.GetString("name");
                Console.WriteLine(u.id);
                list.Add(u);
            }
        }

        public string to_json()
        {
            return JsonConvert.SerializeObject(list);
        }
    }

}
