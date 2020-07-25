#include <iostream>
#include <Hyades.hpp>

class ClientApplication : public Hyades::Application
{
    private:

    public:
        ClientApplication();
        ~ClientApplication();
};

ClientApplication::ClientApplication()
{   }

ClientApplication::~ClientApplication()
{   }

Hyades::Application* Hyades::createApplication()
{
    return new ClientApplication();
}


