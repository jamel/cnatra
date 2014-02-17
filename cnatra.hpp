//
//  cnatra.hpp
//  cnatra
//
//  Created by Sergey Polovko on 1/13/14.
//  Copyright (c) 2014 Sergey Polovko. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_map>

namespace cnatra {
    typedef std::unordered_map<std::string, std::string> data;

    class request : public data {};

    class response : public data {
    public:
        virtual ~response() {}
        friend std::ostream& operator<<(std::ostream& out, const response& r) {
            out << "response";
            return out;
        }
    };

    class service {
    public:
        service() {}


//        template <typename Handler>
//        void get(std::string path, Handler h) {
//            std::cout << "GET " << path << " => " << h() << std::endl;
//        }

        template <typename Handler>
        void get(std::string path, Handler h) {
            std::cout << "GET " << path << " => " << h() << std::endl;
        }

        template <typename Handler>
        void post(std::string path, Handler h) {
            request params;
            std::cout << "POST " << path << " => " << h(params) << std::endl;
        }

        void listen(int port) {
            std::cout << "listen to http://localhost:" << port << std::endl;
        }

        void assets(std::string url, std::string path) {
            std::cout << "serve static assets from " << path << " into " << url << std::endl;
        }
    };

    class view : public response {
    public:
        view(std::string name, data d): name(name), d(d) {}
        friend std::ostream& operator<<(std::ostream& out, const view& v) {
            out << "render view \"" << v.name << "\" with ";
            for (data::const_iterator it=v.d.begin(); it != v.d.end(); ++it) {
                out << it->first << ": " << it->second << ", ";
            }
            return out;
        }
    private:
        std::string name;
        data d;
    };

    class redirect : public response {
    public:
        redirect(std::string url): url(url), code(302) {}
        redirect(std::string url, int code): url(url), code(code) {}
        friend std::ostream& operator<<(std::ostream& out, const redirect& r) {
            out << r.code << " redirect to \"" << r.url << "\"";
            return out;
        }
    private:
        std::string url;
        int code;
    };
}

