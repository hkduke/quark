Quark
--------------------------------
- highlevel features:
    - sharded kv
    - binlog(WAL)
    - master-slave binlog/ m-s + quorum/raft
    - eventual/strongly consistent



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
 - logging.
