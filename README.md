# java_my_rmi
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
