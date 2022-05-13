#include <iostream>
#include <string>
#include <set>
using namespace std;

// an E-mail application
// an message can be in multiple folders
// a folder can save multiple messages

class Folder;

class Message
{
    friend void swap(Message& lhs, Message& rhs);
    friend class Folder;
private:
    string contents;
    set<Folder*> folders;
    // auxiliary funtions
    void addToFolders(const Message& m); // add message to all folders in m.folders
    void removeFromFolders(); // remove message from all folders in m.folders
public:
    Message(const string& str = "") : contents(str) {}
    Message(const Message& m);
    Message& operator=(const Message& rhs);
    ~Message();
    void save(Folder& f); // save message to folder
    void remove(Folder& f); // remove message from folder
};

class Folder
{
private:
    set<Message*> messages;
public:
    Folder() {}
    Folder(const Folder& f);
    Folder& operator=(const Folder& f);
    ~Folder();
    void addMsg(Message* m);
    void removeMsg(Message* m);
};

// Message
// add message to all folders in m.folders
void Message::addToFolders(const Message& m)
{
    for (auto f : m.folders)
    {
        f->addMsg(this);
    }
}

// remove message from all folders in m.folders
void Message::removeFromFolders()
{
    for (auto f : folders)
    {
        f->removeMsg(this);
    }
}

Message::Message(const Message& m) : contents(m.contents), folders(m.folders)
{
    addToFolders(m);
}
Message& Message::operator=(const Message& rhs)
{
    removeFromFolders();
    contents = rhs.contents;
    folders = rhs.folders;
    addToFolders(rhs);
    return *this;
}

Message::~Message()
{
    removeFromFolders();
}

// save message to folder
void Message::save(Folder& f)
{
    folders.insert(&f);
    f.addMsg(this);
}

// remove message from folder
void Message::remove(Folder& f)
{
    folders.erase(&f);
    f.removeMsg(this);
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
    {
        f->removeMsg(&lhs);
    }
    for (auto f : rhs.folders)
    {
        f->removeMsg(&rhs);
    }
    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);
    for (auto f : lhs.folders)
    {
        f->addMsg(&lhs);
    }
    for (auto f : rhs.folders)
    {
        f->addMsg(&rhs);
    }
}

// Folder
Folder::Folder(const Folder& f) : messages(f.messages)
{
    for (auto m : messages)
    {
        m->save(*this);
    }
}

Folder& Folder::operator=(const Folder& f)
{
    for (auto m : messages)
    {
        m->remove(*this);
    }
    messages = f.messages;
    for (auto m : messages)
    {
        m->save(*this);
    }
    return *this;
}

Folder::~Folder()
{
    for (auto m : messages)
    {
        m->remove(*this);
    }
}

void Folder::addMsg(Message* m)
{
    messages.insert(m);
}

void Folder::removeMsg(Message* m)
{
    messages.erase(m);
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
