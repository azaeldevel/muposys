
string inputsparams = Console.ReadLine();
string[] pars = inputsparams.Split('&');
string[] pair;
string key, value;
Dictionary<string, string> POST = new Dictionary<string, string>();

foreach (string str in pars)
{
    pair = str.Split('=');
    if (pair.Length > 0) key = pair[0];
    else key = "";
    if (pair.Length > 1) value = pair[1];
    else value = "";
    POST.Add(key,value);
}

int counter = Int32.Parse(POST["counter"]);

Console.Write("Content-type: text/html\n\n");
Console.Write(counter + 1);

