#pragma once

#include <AK/AKString.h>
#include <AK/CircularQueue.h>
#include <AK/Retainable.h>
#include <AK/RetainPtr.h>
#include <SharedGraphics/Color.h>

class IRCLogBufferModel;

class IRCLogBuffer : public Retainable<IRCLogBuffer> {
public:
    static Retained<IRCLogBuffer> create();
    ~IRCLogBuffer();

    struct Message {
        time_t timestamp { 0 };
        char prefix { 0 };
        String sender;
        String text;
        Color color { Color::Black };
    };

    int count() const { return m_messages.size(); }
    const Message& at(int index) const { return m_messages.at(index); }
    void add_message(char prefix, const String& name, const String& text, Color = Color::Black);
    void add_message(const String& text, Color = Color::Black);
    void dump() const;

    const IRCLogBufferModel* model() const { return m_model.ptr(); }
    IRCLogBufferModel* model() { return m_model.ptr(); }

private:
    IRCLogBuffer();
    Retained<IRCLogBufferModel> m_model;
    CircularQueue<Message, 1000> m_messages;
};
