### CPOL 和 CPHA
#### CPOL(0)  CPHA(0)
      (read)
          ______           ______
         |      |         |      |         ....... SCK
    _____|      |_________|      |_________
              (lock)

#### CPOL(0)  CPHA(1)
             (read)
          ______           ______
         |      |         |      |         ....... SCK
    _____|      |_________|      |_________
                        (lock)

#### CPOL(1)  CPHA(0)
       (read)
    _____        _________        _________
         |      |         |      |         ....... SCK
         |______|         |______|
              (lock)

#### CPOL(1)  CPHA(1)
              (read)
    _____        _________        _________
         |      |         |      |         ....... SCK
         |______|         |______|
                        (lock)

#### Related
[[develop/Protocols/Communication/CommonKnowledge/Serial/Serial|串行]]