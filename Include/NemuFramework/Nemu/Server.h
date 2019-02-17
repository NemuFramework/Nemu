/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _NEMUFRAMEWORK_NEMU_SERVER_H_
#define _NEMUFRAMEWORK_NEMU_SERVER_H_

#include <vector>
#include <string>
#include <memory>

namespace Nemu
{

class Server
{
public:
    class Observer
    {
    public:
        virtual void onServerStarted(const Server& source);
        virtual void onServerStopped(const Server& source);
        virtual void onConnectionOpened(const Server& source, const std::string& sourceAddress);
        virtual void onConnectionClosed(const Server& source, const std::string& sourceAddress);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notify(void (Observer::*fct)(const Server& source), const Server& source);
        void notify(void (Observer::*fct)(const Server& source, const std::string& sourceAddress),
            const Server& source, const std::string& sourceAddress);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    Server(std::shared_ptr<Observer> observer);
    virtual ~Server() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void join() = 0;

    virtual bool isRunning() const = 0;

    Observers& observers();

private:
    Observers m_observers;
};

}

#include "linkoptions.h"

#endif
