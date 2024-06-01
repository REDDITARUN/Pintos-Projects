# -*- perl -*-
use strict;
use warnings;
use tests::tests;
check_expected ([<<'EOF']);
(pa0) begin
(pa0) Test 0 beginning
(pa0) Test thread priority is 63
(pa0) Test thread priority is 62
(pa0) Test thread priority is 61
(pa0) Test thread priority is 60
(pa0) Test thread priority is 59
(pa0) Test thread priority is 58
(pa0) Test 0 Finished
(pa0) end
EOF
pass
