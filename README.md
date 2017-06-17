# java_c_rpc_communication
- 大学課題:JavaとCでRMIのサーバとクライアントを実装する

## 課題内容
- RMIはJavaの環境(サーバもクライアントもJava)でRPCを実現する技術である.
- RMIでサーバオブジェクトのメソッドを呼び出すには，
    - 1. サーバでリモートオブジェクトを登録し，
    - 2. クライアントからサーバのリモートオブジェクトを取得，
    - 3. リモートオブジェクトのメソッドを実行，という手順で行う.
- この時，リモートオブジェクト，およびメソッドの実行でやり取りされるオブジェクトはシリアライズ/デシリアライズされて送受信される.　
- そこで，サーバはJava，クライアントはC言語で以下に示すリモートオブジェクトのメソッドを呼び出すサーバ (Javaプログラム)とクライアントプログラム(C言語)を実装せよ.

1. サーバは起動時に Task(リモートオブジェクト) のインスタンスを生成し，登録する.
2. サーバが起動した後，クライアントはサーバで生成されたインスタンスを取得する.
3. クライアントは取得したインスタンス(シリアライズされたオブジェクト)を解析し，メンバ変数 str1, str2の値を取得する.そして，それら文字列を連結し，Person.name に代入したあと，このPersonオブジェクトを引数にしてサーバの helloを呼び出す.
4. サーバでは引数(Person)を受け取り，デシリアライズしたオブジェクトを使ってhelloを呼び出す.その結果，サーバのコンソールにstr1+str2の結果が表示される.

```
import java.io.Serializable;
public class Task implements Serializable {
private static final long serialVersionUID = 0x8877665544332211L;
public int v = 0x12345678; public String str1 = ”Hello”; public String str2 = ”japan”; public byte x = 1;
public void hello(Person p) { System.out. println(p.name);
} }
```
- Listing 1: リモートオブジェクトの定義

```
import java.io.Serializable;
public class Person implements Serializable {
private static final long serialVersionUID = 0x1122334455667788L; public String name = ”Jobs”;
```

- Listing 2: リモートオブジェクトでやり取りされる Person クラス

### ヒント:
- クライアントとサーバでは通信は2回行われる(リモートインタフェースの取得とメソッド呼び出し)
- サーバとクライアントでやり取りするプロトコルは独自実装で良い(RMIに従う必要はない).ただし，クライアントとサーバでやり取りされるデータ(シリアライズされたデータ)はJavaの仕様に従う必要がある(そうでないとJava標準のデシリアライザで復元できない).
- Javaのシリアライズ/デシリアライズについては,https://docs.oracle.com/javase/7/docs/platform/serialization/spec/protocol.htmlを参照すると良い.
- クライアントから要求されるメソッドを呼び出すには，Javaのリフレクションを利用すると良い

## コンパイル/実行方法
### Server
- `cd server/src`
- `javac Server.java`
- `java Server`

### Client
- `cd client`
- `cmake .`
- `make`
- `./client` (Serverを起動した状態で)

## 実行結果
### Server

```
Server is running...(port=4000)
Connected to client!
command: Get Task
Disconnected to client : /127.0.0.1:51195
Connected to client!
command: Call Task hello
args bytes lenth: 68
hexdump:
ac ed 00 05 73 72 00 06 50 65
72 73 6f 6e 11 22 33 44 55 66
77 88 02 00 01 4c 00 04 6e 61
6d 65 74 00 12 4c 6a 61 76 61
2f 6c 61 6e 67 2f 53 74 72 69
6e 67 3b 78 70 74 00 0a 48 65
6c 6c 6f 6a 61 70 61 6e
call:
Hellojapan
Disconnected to client : /127.0.0.1:51196
```

### Client

```
Connect to Server!
recv
hexdump:
  0000  ac ed 00 05 73 72 00 04 54 61 73 6b 88 77 66 55  ....sr..Task.wfU
  0010  44 33 22 11 02 00 04 49 00 01 76 42 00 01 78 4c  D3"....I..vB..xL
  0020  00 04 73 74 72 31 74 00 12 4c 6a 61 76 61 2f 6c  ..str1t..Ljava/l
  0030  61 6e 67 2f 53 74 72 69 6e 67 3b 4c 00 04 73 74  ang/String;L..st
  0040  72 32 71 00 7e 00 01 78 70 12 34 56 78 01 74 00  r2q.~..xp.4Vx.t.
  0050  05 48 65 6c 6c 6f 74 00 05 6a 61 70 61 6e        .Hellot..japan
magic:
  0000  ac ed                                            ..
version:
  0000  00 05                                            ..
len : 90 ret : 0
classname:
  0000  54 61 73 6b                                      Task
SerialVersionUID : 0x8877665544332211
newHandle_ncd : 7e0000
prim_type_code : I
fieldname:
  0000  76                                               v
prim_type_code : B
fieldname:
  0000  78                                               x
obj_type_code : L
fieldname:
  0000  73 74 72 31                                      str1
new_handle_ns
newHandle_ns : 0x7e0001
handler_len : 18
obj_type_code : L
fieldname:
  0000  73 74 72 32                                      str2
handle : 7e0001
TC_REFERENCE
END_BLOCKDATA
analyze_superclassdesc:
  0000  70 12 34 56 78 01 74 00 05 48                    p.4Vx.t..H
NullReference
newHandle_no : 7e0002
Integer : 12345678
Byte : 1
new_handle_ns
newHandle_ns : 0x7e0003
handler_len : 5
new_handle_ns
newHandle_ns : 0x7e0004
handler_len : 5
===show task===
v: 0x12345678
x: 1
str1: Hello
str2: japan
===Serialize===
bytes:
  0000  ac ed 00 05 73 72 00 06 50 65 72 73 6f 6e 11 22  ....sr..Person."
  0010  33 44 55 66 77 88 02 00 01 4c 00 04 6e 61 6d 65  3DUfw....L..name
  0020  74 00 12 4c 6a 61 76 61 2f 6c 61 6e 67 2f 53 74  t..Ljava/lang/St
  0030  72 69 6e 67 3b 78 70 74 00 0a 48 65 6c 6c 6f 6a  ring;xpt..Helloj
  0040  61 70 61 6e                                      apan
Connect to Server!
fin
```

## 定義した通信プロトコル
- `<command><length><datas>`
- commandは `Get` or `Call` + `Task`(クラス名) + `呼び出し関数名`(Callの時)
- length は `datas` の長さ
- datas はJavaのObject Serialization Stream Protocolに準じる

## 苦労した点
- 全部
    - C言語の書き方やメモリ管理(mallocやポインタなど)について忘れていたので時間がかかった
    - JavaのObject~Streamを初めて使った
