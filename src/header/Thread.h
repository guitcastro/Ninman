#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

class Thread {
        public:
                Thread();
                ~Thread();
                void Start();
                void Wait();
                void Abort();
                void Detach();
                pthread_t GetId();

        protected:
                static void *entryPoint(void *pthis);
                virtual void run() = 0;

        private:
                pthread_t m_threadId;
};

#endif