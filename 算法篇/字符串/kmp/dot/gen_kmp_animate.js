//template
const fs = require("fs")

var a = "abababaac"
var b = "ababa"
a = ' '+a
b = ' '+b
var len_a = a.length-1
var len_b = b.length-1

class template {
  constructor(){
    this.template = `graph g{
    node[shape=plaintext fillcolor=white colorscheme=accent8 ];
    a[
        label=< <TABLE CELLBORDER="1" BORDER="0" CELLSPACING="0" CELLPADDING="0">
            <tr>
                <td border="0">A:</td>
                #1
            </tr>
            <tr>
                <td border="0">B:</td>
                #2
            </tr>
        </TABLE> >
    ]
}`
    this.create_idx = 0;
    this.line_a = ''
    this.line_b=''
    this.dot = ''
  }

  create_line_b_with_no_match(pos_b,pos_a){
    let blank_td = Array(Math.abs(pos_b-pos_a)).fill().map(ch=>`<td border="0"></td>;`).join('')+'\n'
    let line_b = Array.from(b.slice(1)).map( (ch,idx)=> {
      if(idx<pos_b-1) return `<td bgcolor="1">${ch}</td>;`
      else if(idx == pos_b-1) return `<td bgcolor="6">${ch}</td>;`
      return `<td>${ch}</td>;`
    }).join('\n')
    this.line_b  = blank_td+line_b
  }

  create_line_b_move(pos_b,pos_a){
    pos_b++;
    let blank_td = Array(Math.abs(pos_b-pos_a)).fill().map(ch=>`<td border="0"></td>;`).join('')+'\n'
    let line_b = Array.from(b.slice(1)).map( (ch,idx)=> {
      if(idx<pos_b-1) return `<td bgcolor="1">${ch}</td>;`
      //else if(idx == pos_b-1) return `<td bgcolor="6">${ch}</td>;`
      return `<td>${ch}</td>;`
    }).join('\n')
    this.line_b  = blank_td+line_b
  }

  create_line_b_eq(pos_b,pos_a){
    let blank_td = Array(Math.abs(pos_b-pos_a)).fill().map(ch=>`<td border="0"></td>;`).join('')+'\n'
    pos_b++;
    let line_b = Array.from(b.slice(1)).map( (ch,idx)=> {
      if(idx<pos_b-1) return `<td bgcolor="1">${ch}</td>;`
      //else if(idx == pos_b-1) return `<td bgcolor="6">${ch}</td>;`
      return `<td>${ch}</td>;`
    }).join('\n')
    this.line_b  = blank_td+line_b
  }

  write(pos_a){
    this.line_a = Array.from(a.slice(1)).map( (ch,idx)=> idx+1==pos_a ? `<td border="2">${ch}</td>;` :`<td >${ch}</td>;` ).join('\n')
    this.dot = this.template.replace('#1', this.line_a).replace('#2', this.line_b)
    fs.writeFileSync(`kmp_${++this.create_idx}.dot`,this.dot,{encoding:'utf-8'})
  }
}

var temp = new template()


// deal next
var i ,j = 0;
next = Array(len_b).fill(0);
for( i =2;i<=len_b;i++){
  while( j && b[j+1] != b[i] ) j = next[j];
  if( b[j+1] == b[i]) j++;
  next[i] = j;
}

console.log(next)

var cnt = 0;
// kmp
j = 0
for( i =1;i<=len_a ;i++){
  while(j !=0 && b[j+1] != a[i] ) {
    // 1. b[j+1] 与 a[i] 不相等
    temp.create_line_b_with_no_match(j+1, i)
    temp.write(i)
    // 2. 移动
    j =next[j];
    temp.create_line_b_move(j, i);
    temp.write(i)
  }
  if(b[j+1] == a[i] ) {
    // 3.前j个元素相等
    j++;
    temp.create_line_b_eq(j, i);
    temp.write(i)
  }
  if( i== 5){
    console.log(j)
    console.log(len_b)
  }
  if( j == len_b){
    // 4.计数
    cnt++;
    // 5.移动
    j= next[j];
    temp.create_line_b_move(j, i+1);
    temp.write(i)
    console.log("== "+temp.create_idx)
  }
}
