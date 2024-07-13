namespace cs
{
    public class User
    {
        public int id { get; set; }
        public int person { get; set; }
        public string? name { get; set; }
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
            list = new List<User>
            {
                new User()
                {
                    id = 1,
                    person = 1,
                    name = "user1"
                },
                new User()
                {
                    id = 2,
                    person = 2,
                    name = "user2"
                },
                new User()
                {
                    id = 3,
                    person = 3,
                    name = "user3"
                },
                new User()
                {
                    id = 4,
                    person = 4,
                    name = "user4"
                }
            };

        }
        public List<User> GetUsers()
        {
            return list;
        }

        public User GetUser(int id)
        {
            var user = list.FirstOrDefault(x => x.id == id);
            return user;
        }
    }
}
