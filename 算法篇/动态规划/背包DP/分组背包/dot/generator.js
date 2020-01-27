const fs = require("fs")
var cnt = 0;
var w = [
  [0,0,0,0,0,0],
  [0,1,2,3],
  [0,1,2,3],
]
var v = [
  [0,0,0,0,0,0],
  [0,1,2,3],
  [0,3,2,1],
]
var N = 2,C = 3;
var num = [0,3,3]

var f=[]
for(let i = 1;i<=100;i++)
  f.push(0)

generator(-1, -1,0,0,C)
let i,j,k;
for(i=1;i<=N;i++) //枚举物品
{
    for(k=C;k>=0;k--){
      for( j = 1;j<=num[i];j++){
        if( w[i][j] > k) continue;
        f[k] = Math.max(f[k],f[k-w[i][j]]+v[i][j])
        generator(k, k-w[i][j],i,j,k)
      }
    }
}

console.log(f[C])

function generator(now,pre,i,j,k){
  var template = `
digraph g {
    node[shape=plaintext fixedsize=true  colorscheme=accent8 ];
    t1;
    a[
        label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="0" CELLPADDING="10">
            <tr>
                <td PORT="f0" ${ now == 0 ?'BGCOLOR="1"' :''}>${f[0]}</td>
                <td PORT="f1" ${ now == 1 ?'BGCOLOR="1"' :''}>${f[1]}</td>
                <td PORT="f2" ${ now == 2 ?'BGCOLOR="1"' :''}>${f[2]}</td>
                <td PORT="f3" ${ now == 3 ?'BGCOLOR="1"' :''}>${f[3]}</td>
            </tr>
        </TABLE> >
    ];
    t2;
    b[
        label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="0" CELLPADDING="2" cellborder="0">
            <tr>
                <td PORT="">组:</td>
                <td PORT="">${i}</td>
            </tr>
            <tr>
                <td PORT="">物品:</td>
                <td PORT="">${j}</td>
            </tr>
            <tr>
                <td PORT="">容量:</td>
                <td PORT="">${k}</td>
            </tr>
        </TABLE> >
    ]
    a:f0:s->b[style=invis];
    b->t3[style=invis];
    ${
      pre < 0 ? '' :
      'a:f'+now+':n->a:f'+pre+':n;'
    }

    t1,t2,t3[style=invis]
}
`

  fs.writeFileSync(`fenzu_${++cnt}.dot`,template ,{encoding:'utf-8'})
}
