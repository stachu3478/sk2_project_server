#include "message/SimpleMessageOut.h"
#include "../net/Client.h"
#include "Player.h"
#include "../spec/spec.h"

using namespace std;

class ClientMock : public Client {
    public:
        ClientMock() {};
        virtual ~ClientMock() {};

        void flush() { assertTrue(flushes, "Flushed unexpectectly"); flushed = true; };
        void emit(MessageOut* m) { m->length(); assertTrue(emits, "Emitted unexpectectly"); emitted = true; };
        bool isOffline() { return offline; };

        void disconnect() {};
        void setMessageIdentifier(MessageIdentifier* i) { i->setFd(0); };
        MessageIdentifier* getMessageIdentifier() { return nullptr; };

        bool flushes = false;
        bool emits = false;
        bool offline;

        bool flushed = false;
        bool emitted = false;        
};

class SimpleMessageOutMock : public SimpleMessageOut {
    public:
        char getType() { return 123; };
};

typedef std::shared_ptr<ClientMock> ClientMockPtr;

int main(int argc, char* argv[]) {
    ClientMockPtr c { new ClientMock() };
    Player p(std::dynamic_pointer_cast<Client>(c));
    it("returns_offline_status_of_client_true", [&]{
        c->offline = true;
        assertTrue(p.isOffline());
    });
    it("returns_offline_status_of_client_false", [&]{
        c->offline = false;
        assertFalse(p.isOffline());
    });
    it("emits_messages_when_online", [&]{
        SimpleMessageOutMock m;
        c->offline = false;
        c->emits = true;
        p.emit(&m);
        assertTrue(c->emitted);
    });
    it("does_not_emit_messages_when_offline", [&]{
        SimpleMessageOutMock m;
        c->offline = true;
        p.emit(&m);
        assertFalse(c->emitted);
    });
    it("flushes_messages_when_online", [&]{
        c->offline = false;
        c->flushes = true;
        p.flush();
        assertTrue(c->flushed);
    });
    it("does_not_flush_messages_when_offline", [&]{
        c->offline = true;
        p.flush();
        assertFalse(c->flushed);
    });

    return run(argc, argv);
}