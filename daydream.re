#@# VRコンテンツのつくりかた2 技術書典3
#@# （）かっこは全角統一する。
#@# ユーザ入力は""ダブルクォーテーション、メニュー表示文字列は「」かぎかっこにでくくる。

= Daydreamを知る

//image[daydream-logo][Daydreamロゴ][scale=0.50]

== Daydreamとは

Daydreamとは、GoogleのAndroidスマートフォン向けVRプラットフォームです。
ハードウェアからアプリマーケットまでを含む統合プラットフォームであり、主に以下に示す要素から構成されています。

 * Daydream-readyと呼ばれる高スペックのAndroidデバイス
 * ジャイロ・加速度センサを搭載し、Bluetoothで接続するコントローラとセットになったヘッドユニットのDaydream View
 * Android 7.0（Nougat）以降での、低い入力遅延・高速な描画処理のためのAndroid OS内部での特別な対応
 * Google Playとシームレスに融合し、HMDを装着したままでアプリのインストールから起動を行えるランチャー機能をもった専用のホームアプリ

それぞれの要素について、詳細を示します。

=== Daydream-ready phones

//image[daydream-ready-phone-requirements][Daydream-ready phonesの3要件][scale=0.75]

その母艦となるハードウェア要件があり、それを満たしたものをDaydream-ready phones@<fn>{daydream-ready-phones}と呼びます。
SoC、センサ、ディスプレイの3つの要件があります。

 * 3D画像処理とFPSを維持するための高いパフォーマンスを有するSoC
 * 姿勢予測のための高い分解能と低遅延のセンサ
 * 高い応答速度、低遅延のディスプレイ

Socについては、現状Daydream-ready phonesに認定されているAndroidデバイスから判断するとSnapdrago 820以上であれば満たすと考えられます。
ただし、「MediaTekがDaydreamのためのSoCを開発する」というニュース@<fn>{daydream-ready-soc-mediatek}も発表されており、Snapdragonに限定はされていない模様です。

ディスプレイについては、現時点では種々の応答性能の都合上有機ELのみが採用されています。
「JDIの開発したVR専用の超高精細・高速応答　液晶ディスプレイ@<fn>{jdi-lcd-for-vr}」のように、同等の性能があれば液晶ディスプレイでも要件を満たすと考えられます。
将来はLCDを搭載したDaydream-ready phonesも登場するでしょう。

//footnote[daydream-ready-phones][Daydream-ready phones @<href>{https://vr.google.com/daydream/phones/}]
//footnote[daydream-ready-soc-mediatek][MediaTek's Next-Gen SoCs To Support Google's Daydream | Androidheadlines.com @<href>{https://www.androidheadlines.com/2016/05/mediateks-next-gen-socs-support-googles-daydream.html}]
//footnote[jdi-lcd-for-vr][ニュース＆イベント : ニュースリリース | 株式会社ジャパンディスプレイ @<href>{http://www.j-display.com/news/2016/20161121.html}]

=== Daydaream Viewとコントローラ

//image[daydream-view-controller][Daydream View（旧型）と専用コントローラ][scale=0.75]

==== 専用コントローラ

DaydreamのVRアプリを体験するには、レンズ付きヘッドユニットがセットになったDaydream View@<img>{daydream-view-controller}本体と、Bluetooth接続の専用コントローラが必要です。

このレンズつきヘッドユニット部ですが、特別な回路は搭載されていないため、レンズ部分が同等であれば、実は別のCardboardゴーグルを利用しても動作させることができます。
旧型のDaydream ViewにはNFCタグが埋め込まれており、初回セットアップ時に読み込んでいましたが、不要になっていました。
新型のDaydream ViewにはNFCタグは搭載されていないのかもしれません。

このコントローラはIMUセンサを含み、クリックのできるタッチパッド、Appボタン、Homeボタンとボリュームボタンを持ちます。
また、Bluetoothで母艦であるDaydream-readyのAndroidデバイスと接続して動作します。

このコントローラですが、BLEデバイスとしては単純なつくりになっています。
Bluetooth LE（Low Energy）の用語で言うと、「あるServiceのあるCharacteristicで3種のセンサとボタン・タッチパッドの情報をbit列にしてNotifyしているだけ」です。

==== Daydreamコントローラのハック

「iPhoneでもDaydreamコントローラは使えないか？」という話に始まり、Daydreamコントローラをハックした事例があります。
センサ類のイベント情報をBLE経由で取得し、解析するに至った流れが「How I hacked Google Daydream controller – Hacker Noon@<fn>{daydream-controller-hack}」というblogエントリに掲載されています。
最終的にはA-Frameを用いたiPhone上のHTMLコンテンツ上でDaydreamコントローラの情報がとれるところまで簡潔にまとまっており、全貌を読み取るには少々のBLEの知識が必要ですが、ぜひ読んでみてください。

このハック内容によると、Daydreamコントローラはセンサ情報をBluetooth LEのGATT NotifyでCentral（スマートフォン母艦）側に送信し続けています。
その内容は、ジャイロ・地磁気・加速度センサそれぞれのX軸・Y軸・Z軸の情報、Home・App・VolumeUp・VolumeDown・タッチパッドのクリック状態の各ボタンのon/off情報、タッチパッドのXY座標の情報などがぎゅっと160bitのbit列に詰められています。
複雑な式による計算結果や、暗号化されたデータではないとのことです。

このことより、Daydreamのコントローラ側はシンプルにIMUセンサの取得値やボタン類の状態を送信するだけのつくりになっており、賢いアームモデルのエミュレーションはスマートフォン内部で行なっていることがわかります。

//footnote[daydream-controller-hack][How I hacked Google Daydream controller – Hacker Noon @<href>{https://hackernoon.com/how-i-hacked-google-daydream-controller-c4619ef318e4}]

=== 新型のDaydream Viewについて

//image[new-daydream-view][新型のDaydream View][scale=0.75]

つい先日の2017年10月4日、Googleの新Product発表会が行われ、話題のGoogle HomeファミリーやPixel 2/Pixel 2 XLとあわせて、新型のDaydream View@<fn>{new-daydream-view}が発表されました（@<img>{new-daydream-view}）。
特徴と、気になるポイントを以下に述べます。

 * 重いAndroidデバイスを装着時にバランスが悪くなりやすかったため、取り外し可能な上部のバンドを追加。あわせて頰にあたる部分のクッション形状を変更
 * 熱暴走対策として、抑え蓋がヒートシンクの役割をするように
 * 価格は$99
 ** $20アップ
 * 日本でも発売予定あり
 * 視野角が10度ほど向上
 ** 約90度→約100度
 ** シンプルな凸レンズから、特殊な形状のフレネルレンズに変更
 * IPD調節機構はなし

値段アップは残念です。
安価な中国製Cardboard HMDが近年徐々に使い勝手がよくなってきている流れを汲んで、できれば値下げしてほしかったです。
物価が気軽に上昇しがちなシリコンバレー感覚では、パワーアップしたのにおおむね価格据え置きで「勉強しました」という感覚なのかもしれません。

新型Daydream Viewについて、GoogleがYouTubeにプロモーション動画を公開しています@<fn>{new-daydream-view-youtube}。
この動画中に出てくるChromecastを使った、外部ディスプレイへのキャストは、10月上旬ごろからすでに既存のDaydreamで使えるようになっています。
Daydreamアプリのホーム画面から「キャスト」を選択すると常時ストリーム状態になります。
パフォーマンスには影響がありそうですが、大きな遅延はなくきちんと動作しており、デモなどいくつかのシーンでは役に立ちそうです。

Googleのblogには年内発売と述べられています@<fn>{pixel2-and-daydream}ので、あわせてDaydream 2.0 EuphratesアップデートやHMDを外す必要がないフルVRモードのChromeアップデートもあわせて行われることを期待しています。

//footnote[new-daydream-view][Google Daydream View Tech Specs - Google Store @<href>{https://store.google.com/us/product/google_daydream_view_specs?hl=en-US}]
//footnote[new-daydream-view-youtube][Meet Google Daydream View | Dream with your eyes open - YouTube @<href>{https://www.youtube.com/watch?v=PNBL2DpB1YE}]
//footnote[pixel2-and-daydream][Pixel 2 and Daydream View: new experiences in AR and VR @<href>{https://www.blog.google/products/google-vr/pixel-2-and-daydream-view-new-experiences-ar-and-vr/}]

=== Android 7.0 NougatとVRモード

Android 7.0 NougatでDaydreamのために特別な対応が入り、AndroidプラットフォームとしてはVRモードというものが定義されました。
Androidデバイスの互換性について定義したCDD@<fn>{android-cdd}というドキュメントがあり、にVirutal Realityの項目があります。
Daydream対応Androidデバイスをつくる仕事でもしていなければあまり役には立たない話なのですが、VRモードの定義の他、「DadyreamというVirtual Reality要件に対応したAndroidデバイスはどんな条件を満たさないといけないのか」という観点は面白いので、少しCDDを見ていきましょう。

CDDの「7.9. Virtual Reality」の項目@<fn>{android-cdd-vr}に「7.9.1. Virtual Reality Mode」という記載があり、そこでは「VRモードをサポートすること。そのモードでは、通知などを双眼のHMDのためにステレオでレンダリングし、VRアプリケーションが動作している間はモノラル（単眼）のシステムUIを無効化すること。」とあります。
ディスプレイの黒挿入モードやフレームバッファへのダイレクトレンダリング、センサ情報の低遅延伝達あたりはこの「VRモード」と直接は関係ない模様です。

//image[cdd-vr][CDD 7.9.2 Virtual Reality High Performance（冒頭）][scale=1]

つづけて「7.9.2 Virtual Reality High Performance」という項目に"high performance VR"という表現で、Daydreamの要件が記載されています（@<img>{cdd-vr}）。
一部を抜粋して紹介します。

 * これらの要件は@<code>{android.hardware.vr.high_performance} feature flagを有効にするのに必要な項目である
 * [C-1-2] @<code>{android.software.vr.mode} feature flagの宣言が必須である

Feature Requirements@<fn>{daydream-feature-requirements}に記載されている通り、この二項目が「Daydreamが有効であるか」を判定するためのフラグになっています。
逆に言うと、Android 7.0 Nougat以降を搭載しており、rootedなAndroidデバイスに必要なapkなどを移植してこのフラグを有効にすると、非対応デバイスであってもDaydreamが動作することが確認されています@<fn>{daydream-force}。
実態としてはSnapdragon820以降であれば快適に動くとのことで、このCDDで記載された要件を満たしていればそりゃ動かないはずはないよね、という話の模様です@<fn>{android-well-done}。

//footnote[android-well-done][Androidよくできてんな。]

 * [C-1-11] 最低でも3840x2160@30fps-40MbpsのH.264のデコードのサポートが必須である（1920x1080@30fps-10Mbpsが4つ、あるいは1920x1080@60fps-20Mbpsが2つ同時にデコード可能、に相当）
 * [C-1-12] 最低でも1920x1080@30fps-10MbpsのHEVCとVP9のデコードのサポートが必須、できれば3840x2160@30fps-20Mbpsに対応すべき（1920x1080@30fps-5Mbpsが4つ同時にデコード可能、に相当）
 
4KのH.264は対応してくれないと困るよ、というのが読み取れます。
4K HEVCはSHOULDで書かれているので少し弱めです。

 * [C-1-14] スクリーン解像度はフルHD（1080p）が必須、QuadHD（1440p）以上を強く推奨
 * [C-1-15] ディスプレイサイズは4.7インチから6.3インチの間であること
 * [C-1-16] ディスプレイはVRモード時に最低60Hzで動作すること
 * [C-1-17] ディスプレイはGray-to-Gray、White-to-Black、Black-to-Whiteがの応答性能が3ms以下であること
 * [C-1-18] ディスプレイは残像が5ms以下の低残像モードの対応が必須

このあたりがディスプレイ要件ですね。現時点のDaydream対応スマートフォンは全て有機ELですが、VR向けの低残像・高密度・高い開口率の液晶が徐々に発表されるプロダクトにも適用されはじめています@<fn>{oculus-go-lcd}。

 * [C-1-19] Bleuetooth 4.2とBluetooth LE（Low Energy）とData Length Extension対応必須

BLEはDaydreamコントローラ用の要件です。

 * [SR] @<code>{android.hardware.sensor.hifi_sensors}の対応を強く推奨
 
hifi sensorはAndroid 6.0から定義が追加された「高い忠実性（high fidelity）をもつセンサ」のことです。
Androidの要件としては加速度センサやジャイロセンサは「50Hzが必須」レベルなのですが、hifi sensorでは「400Hzまたはそれ以上が必須」となっています。
頭部の姿勢予測に使われるものと考えられます。

//footnote[android-cdd][Android Compatibility Definition Document @<href>{https://source.android.com/compatibility/cdd}]
//footnote[android-cdd-vr][Android CDD 7.9. Virtual Reality - @<href>{https://source.android.com/compatibility/android-cdd#7_9_virtual_reality}]
//footnote[daydream-feature-requirements][Daydream Feature requirements @<href>{https://developers.google.com/vr/distribute/daydream/functionality-requirements}]
//footnote[daydream-force][Reddit Got Daydream to work on my 5X, might work on other Android 7.0 phones as well @<href>{https://www.reddit.com/r/Android/comments/5hno6u/got_daydream_to_work_on_my_5x_might_work_on_other/}]
//footnote[oculus-go-lcd][Pioneering the Frontier of VR: Introducing Oculus Go, Plus Santa Cruz Updates @<href>{https://www.oculus.com/blog/pioneering-the-frontier-of-vr-introducing-oculus-go-plus-santa-cruz-updates/}]

== CardboardとDaydreamの歴史的経緯

2014年5月、Google I/O 2014のkeynoteで、ダンボールにアクリル製レンズをはめ込んだゴーグル型のVRデバイス、Cardboardが発表されました。
Googleが設計図を公開したことと、その構成要素がシンプルであったため、互換品が数多く制作され、世界中に広まっていきました。

Oculus Rift DK1/DK2によって確立された、ジャイロセンサによる姿勢予測、スマートフォン向けの（安価な）高精細で応答速度に優れた有機ELディスプレイと、複雑な光学系機構の代わりにソフトウェア側でレンズにあわせて画面表示を歪めておく樽型歪み補正（Barrel Distortion）を組み合わせ、安価なデバイスで高度なVR体験を実現する手法を、そのままその要素を搭載したスマートフォンで実現したのがCardboardでした。

ところが、Cardboardはあくまでエントリー向け、PCのそれと比較して機能が劣るのはもちろん、場合によっては安かろう悪かろう低品質なVR体験デバイスとしての地位を確立してしまいました。

主に3つの要因があります。
1つ目は、Androidデバイスにとって加速度・地磁気・ジャイロセンサの高い測定分解能がハードウェアとしての必須要件ではなかったこと。
特にローエンドのAndroidデバイスに多いジャイロセンサ未搭載のデバイスではドリフト対応の副作用として、Google VR SDKは正常に動作しません。
2つ目は、幅広いAndroidデバイスのスペックバリエーションに対して、VR空間を実現するのに十分なクォリティで60fpsを維持したCGのレンダリングが大変シビアであったこと。
3つ目に、いわゆる「360度動画」と呼ばれる、ステレオ全天球などの形式である動画コンテンツの大きな解像度・fpsを問題なく扱うことができるハードウェアチップはごくハイエンド向けに限られることが挙げられます。

そんな状況の中、2016年5月、Google I/O 2016にて、Google VRの新たなプラットフォームとしてDaydreamが発表されました。
Daydreamは前述の問題点が、特定の基準を満たしたハードウェア要件を満たすDaydream-ready phonesと、Androidプラットフォームとしてのソフトウェアでの対応が密に連携することで解決されます。
また、それらに加えてコントローラの標準装備、HMDを外すことなくアプリを切り替えることができるホーム・ランチャー対応とGoogle Playへの融合、「なるべく快適にコンテンツを楽しむ効率をあげる」ための工夫がDaydreamにはたくさんつまっています。

モバイルVRの基準が、Daydream級にすみやかに移行してほしいと思います@<fn>{ios-12-vr}。

//footnote[ios-12-vr][iOS 12でVRKitが出て、オルタナティブガールズとかときめきアイドルとかラブプラスEVERYとかがあっさりとCardboardを捨ててくれる未来を夢見ています。]

== Daydream standalone

//image[daydream-standalone-vive-lenovo][Vive（HTC）（左）とLenovo（右）のDaydream standalone][scale=1.00]

2017年5月、Google I/O 2017にて、スタンドアローン型のDaydreamヘッドセット、Daydream standalone@<fn>{daydream-standalone}が発表されました。

ひとことで言うと「Androidが埋まっていて、電源を入れるとDaydreamのホームアプリが立ち上がるVRヘッドセット」です。
特徴はTangoをベースとしたWorldsenseと呼ばれる技術により、ポジショントラッキング（平行移動）に対応していることです。

年内発売予定で、Vive（HTC）製とLenovo製の2つ（@<img>{daydream-standalone-vive-lenovo}）が予定されています。

今のDaydream（Cardboardも同様）はヘッドトラッキングと呼ばれる、頭の向きのみを考慮したトラッキングになっています。
体を大きく前に乗り出したり、敵の弾を避けようと横に上半身を躱すような動作に対応しておらず、そのような動作をした際には体の動きとヘッドセットで表示される視界に不一致が起きるため、酔いに繋がってしまいます。

そのため、現行のDaydreamでは「回らないソファにゆったりと座った状態で軽く首を動かすことを想定し、大きく体をひねって真後ろの敵を撃つようなコンテンツは避けること」といったことがすすめられています@<fn>{vr-ar-mr-google}。

つい先日、Oculus Connect 4で、スタンドアローン型のヘッドセット、Oculus Goが発表されましたので、せっかくなので比較してみましょう（@<table>{daydaream-standalone-oculus-go}）。
どちらも発表時のみの情報であり、実際に発売されるまでには変更される可能性が高いことはご了承願います。


//table[daydaream-standalone-oculus-go][Daydream standaloneとOculus Go]{
項目	Daydream standalone	Oculus Go	備考
--------------------------------------------------------------------------------
ベース技術	Daydream + Tango	Gear VR
発売元	Vive（HTC）, Lenovo	Oculus
アプリストア	Google Play	Oculus Store
価格	未定	$199
SoC	Snapdragon 835	不明
ヘッドトラッキング	対応	対応
ポジショントラッキング	対応（WorldSense）	非対応
発売時期	年内予定	2018年
コントローラ	3DoF + タッチパッド@<br>{} + ボタン	3DoF + タッチパッド@<br>{} + ボタン（トリガ）
//}

Oculus GoはコアとなるSoCについて、その価格からミドルレンジのデバイスであると推測されます。
Daydream standaloneはSnapdragon 835ベースでハイエンドのデバイスであると推測されます。

これらのスタンドアローン機はどのようなメリットがあるのでしょうか。
現行機の「Galaxy S8とGear VRのセットで$749」や「Pixel 2とDaydream Viewのセットで$749」という価格帯は決して気軽にエントリーできるものではありません。
「Oculus Goの$199」や「Daydream standaloneの$599」は販促目的でのVR体験キャンペーンなどに20台とか用意する際の費用や、物理的な取り回しにおいてメリットがある、という無難な期待をしておくのが妥当そうでしょうか。

ただし、そもそも日本での入手性が不明なため、残念ながらどちらも「VRマニアなら持ってる」という一品で終わってしまう可能性もあります。

//footnote[vr-ar-mr-google][VR／AR／MRは「空間的コンピューティング」の波だ　Googleが語るDaydream・Tangoの基礎【Unite】 | PANORA VR @<href>{http://panora.tokyo/27157/}]
//footnote[daydream-standalone][Daydream standalone @<href>{https://vr.google.com/daydream/standalonevr/}]
//footnote[oculus-go][Pioneering the Frontier of VR: Introducing Oculus Go, Plus Santa Cruz Updates @<href>{https://www.oculus.com/blog/pioneering-the-frontier-of-vr-introducing-oculus-go-plus-santa-cruz-updates/}]

== ARとAR Coreとポジショントラッキング

AR戦国時代がいつのまにか始まりました。
HoloLensのMRや、Google TangoもZenFone ARから盛り上がって…と言いたいところですが、そんなことはありません。

写真SNSであるInstagramが台頭する中、楽しく"盛れる"snowなどのアプリによるリアルタイムの画像処理技術の進化競争がある中、"たまたま"ポケモンGOがやってきました。
ポケモンGOで、人は「カメラ映像にCGを重畳するAR」を思い出してしまったのです。
この流れの分かりやすい例としては、Snapchatによる、世界をARで装飾するWorld Lenses@<fn>{snapchat-ar}があります。

ポケモンGOはなんとなくであのUIになってしまったわけではなく、「現実世界に拡張した情報を重ね合せる」という本質的なARサービスであるGoogleマップを開発していたバックグラウンドがあって、十分に人の心が動いて、結果体が動いてもらうための機能を検討をした上で今のような実装になったことが、CEDEC 2017のセッションで説明されています@<fn>{pokemongo-ar}。

そんな中、まっすぐにAR機能を有するARKitがiOS11でやってきました。
ARKitは買収したMetaio@<fn>{apple-metaio}の技術が使われていると言われていますが、こちらもタイミングとしては"たまたま"だと思っています。
なぜなら、歴史的にiOSは「既存のサービスのクローンを作りやすくする機能、あるいはクローンそのもの」をぶつけてくることが多いのですが、ARKitについてはそうではありません。
前述の通りの"盛る"ための機能はiPhone XのTrueDepthカメラシステムによる3Dウ○コのやつです。

そんなARKitを世間はおおいに担ぎ上げたため、Googleは大慌てでTangoをAR Coreに切り替えることになってしまいました。
そのAR CoreはARKitとほぼ同等で、水平面しか検出できず、Depthもとれず、Area Learningによる外界検出結果の保存・読み出しには対応していません。
Tangoと比較して、機能としてはかなりの劣化版です。

本質的なARはGoogleマップですでに日常使われています。「カメラ映像にCGを重畳する」の延長線上としてみんなが期待する電脳メガネやオーグマーは、HoloLensがその入り口に立ったところで、もう少し将来の話です。今のARブームは波がすぎると、現状のニッチであっても市場ができたVRのようには定着しないと思っています。

そんなARKitとAR Coreですが、VRの世界から眺めて「モバイルにポジショントラッキング技術が来た」と考えると、次の一手が楽しみになります。
Windows MRやOculusのSanta Cruzのように複数のカメラでもなければ、TangoやiPhone XのようにDepthカメラを持つわけではない、ハードウェアのシンプルな難易度の高いVisual SLAMにAppleとGoogleというモバイルの二大巨頭がパワーをつぎ込んでくれるわけです。

iOS 12でVRKitが来るのが先か、$199のDaydream standalone 2が来るのが先か、Tangoの取り下げで凹んだ分はきっちり他の分野が凸ってくれるといいなと思っています。

//footnote[snapchat-ar][Snapchat adds world lenses to further its push into augmented reality - The Verge @<href>{https://www.theverge.com/2017/4/18/15333130/snapchat-world-lenses-something-new-for-facebook-to-copy}]
//footnote[apple-metaio][Appleが定評のある拡張現実スタートアップMetaioを買収していた | TechCrunch Japan @<href>{http://jp.techcrunch.com/2015/05/29/20150528apple-metaio/}]
//footnote[pokemongo-ar][『ポケモンGO』を開発したナイアンティックが目指す“世界を動かすAR”【CEDEC 2017】 ファミ通App @<href>{https://app.famitsu.com/20170901_1129022/}]
