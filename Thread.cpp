#include "Thread.h"

Thread::Thread() {
}

Thread::~Thread() {

}

/* static */
void *Thread::entryPoint(void *pthis) {
        Thread *ptr = static_cast<Thread *>(pthis);
        ptr->run();
}

void Thread::Start() {
        int nRet;

        if (pthread_create(&m_threadId, NULL, entryPoint, this) != 0) {
                // throw an error
        }
}

void Thread::Wait() {
        if (pthread_join(m_threadId, NULL) != 0) {
                // throw an error
        }
}

void Thread::Abort() {
        if (pthread_cancel(m_threadId) != 0) {
                // throw an error
        }
}

void Thread::Detach() {
        if (pthread_detach(m_threadId) != 0) {
                // throw an error
        }
}

pthread_t Thread::GetId() {
        return m_threadId;
}