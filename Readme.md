# Serialization

This library supplies generic classes for (reflection like) description of classes, 
their members and function and serialization.

## Benchmark

A few benchmark with different settings are made.
They are made to give a general idea of performance and not
created in a proper environment at all.

Commit | comment |optimization flags | number of runs | time/µs | binary size/kBytes
-|-|-|-|-|-
68b311433f3cdcce37a94a2362fd22652193617c | | -Og -g | 1e7 | 11772837 | 435,0
68b311433f3cdcce37a94a2362fd22652193617c | | -Ofast | 1e7 | 9516451 | 35,7
68b311433f3cdcce37a94a2362fd22652193617c | | -Os | 1e7 | 11239371 | 25,7
bd08f6efdda0a3f76d205ea7154c4b2c7cac9cfe | replaced real file with "/dev/null" | -Og -g | 1e7 | 9057969 | 435,0
bd08f6efdda0a3f76d205ea7154c4b2c7cac9cfe | replaced real file with "/dev/null" | -Ofast | 1e7 | 6845635 | 35,7
bd08f6efdda0a3f76d205ea7154c4b2c7cac9cfe | replaced real file with "/dev/null" | -Os | 1e7 | 8264227 | 25,7
7fd09e440b9419292aba909e1db143d4777f2d51 | removed inheritance, use templates | -Og -g | 1e7 | 8773384 | 451,5
7fd09e440b9419292aba909e1db143d4777f2d51 | removed inheritance, use templates | -Ofast | 1e7 | 6635195 | 25,0
7fd09e440b9419292aba909e1db143d4777f2d51 | removed inheritance, use templates | -Os | 1e7 |  | 8894198 | 19,3

