using cs;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Http;


var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();


UserService users = new UserService();

app.MapGet("/", () => "Hello World!");
//app.MapGet("/user/{id?}", (int? id) => $"A users {id}");
app.MapGet("/api/user/{id?}", (int? id) => { return $"A users {users.GetUser((int)id).id}"; });
app.MapGet("/api/user/name/{id?}", (int? id) => { return $"A users {users.GetUser((int)id).name}"; });


/*app.MapGet("/users", (IUserService userservice) =>
    TypedResults.Ok(userservice.GetUsers()))
    .WithName("GetUsers")
    .WithOpenApi(x => new OpenApiOperation(x)
    {
        Summary = "Get List of Users",
        Description = "Returns information about all the available user from the muposys database.",
        Tags = new List<OpenApiTag> { new() { Name = "Amy's Library" } }
    });*/

app.Run();
