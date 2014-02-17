//
//  main.cpp
//  cnatra
//
//  Created by Sergey Polovko on 1/13/14.
//  Copyright (c) 2014 Sergey Polovko. All rights reserved.
//

#include "cnatra.hpp"

using namespace cnatra;


int main(int argc, const char * argv[])
{
    service s;

    s.get("/ping", [] {
        return "pong";
    });

    s.get("/login", [] {
        data d = {{"name", "Sergey"}, {"age", "18"}};
        return view("login.hbs", d);
    });

    s.post("/login", [] (request& params) -> response {
        if (params["login"] == "jamel" && params["password"] == "123")
            return redirect("/home");

        data d = {{"error", "Invalid username or password"}};
        return view("login.hbs", d);
    });

    s.get("/hello/:name", [](std::string name) {
        return "Hello, " + name + "!";
    });

    s.assets("/static", "static");

    s.listen(8080);
}

