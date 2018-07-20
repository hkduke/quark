Quark
--------------------------------
- highlevel features:
    - sharded kv
    - binlog(WAL)
    - master-slave binlog/ m-s + quorum/raft
    - eventual/strongly consistent
    - protocol - transaction,consistency,heartbeat,version-control protocol
    - thread model
    - i/o model - reactor,preactor,ace
    - direct i/o - 

- MainRoad
 
 - logging utils: 
  - support: rotate size; thread-safe; rich format; operator '<<'.
 
 - sys:
  - threads:
    - worker pool. template --> work_loop.
  - socket programming:
    - socket set async/sync.
    - fd health check: PEEK.
    - poll/epoll: write/read again.
  - libaio


2018.06.24
--------------------------------
 - logging planning.

2018.07.01
--------------------------------
 - NPTL Thread initial version.
 - Posix File Abstraction.
 - 

2018.07.10
--------------------------------
 - add support for gettid(2) as thread id; add a generic syscall wrapper for x86_64.



TODO List
-------------------------------
 - [x] test for thread
 - [x] atomic operation of cas/fad
 - [ ] impl. sync routine by quark atomic operation
 - [ ] add some lock-free datastructure
 - [ ] event frame work
 - [ ] logging module
 -




Test Note
--------------------------------

| module | timestamp | note |
|------|--------|---------------|
| misc | 180625 | unit_test done|
| thread/tid | 180710 | unit_test done|
| atomic | 180718 | basic unit test done |
