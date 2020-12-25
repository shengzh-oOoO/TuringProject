#Q = {start,mva,mvb,readyret,ret,cmp,accept,accept1,accept2,accept3,reject,reject1,reject2,reject3,reject4,halt_reject,halt_accept}
#S = {a,b}
#B = _
#G = {a,b,_,t,r,u,e,f,l,s}
#q0 = start
#F = {halt_accept,halt_reject}
#N = 2
;将第一段a剪切到第2条纸带上
start a_ a_ ** mva
start b_ __ r* reject
start __ __ ** reject
mva a_ _a rr mva
;将第一段b剪切到第2条纸带上
mva b_ b_ ** mvb
mva __ __ ** reject
mvb b_ _b rr mvb
mvb __ __ ** reject
mvb a_ a_ *l ret
;将第二条纸带的指针移回最左端
ret ab ab *l ret
ret aa aa *l ret
ret a_ a_ *r cmp
;开始比较,两条纸带相同则接受,否则拒绝
cmp ab __ r* reject
cmp ba __ r* reject
cmp a_ __ r* reject
cmp b_ __ r* reject
cmp _a __ ** reject
cmp _b __ ** reject
cmp aa __ rr cmp
cmp bb __ rr cmp
cmp __ __ ** accept
;拒绝后需清空纸带1
reject a_ __ r* reject
reject b_ __ r* reject
;打印true
accept __ t_ r* accept1
accept1 __ r_ r* accept2
accept2 __ u_ r* accept3
accept3 __ e_ r* halt_accept
;打印false
reject __ f_ r* reject1
reject1 __ a_ r* reject2
reject2 __ l_ r* reject3
reject3 __ s_ r* reject4
reject4 __ e_ r* halt_reject
