#@# VRコンテンツのつくりかた2 技術書典3
#@# （）かっこは全角統一する。
#@# ユーザ入力は""ダブルクォーテーション、メニュー表示文字列は「」かぎかっこにでくくる。

= UnityでDaydreamアプリ開発の入り口を覗く

さて、概要を知って、使い方を知ったその次は、Daydreamアプリ開発の入り口を覗いてみましょう。

Daydreamも発表されて約1年半、リリースされて約1年経ちました。
Google VR SDK（略称：GVR SDK）として、様々なライブラリやツールが揃ってきております。
古い情報も残っていたり、Cardboard向けやiOS向けの話もあり、さあ冒険に出かけよう、と足を踏み出しても迷子になりやすい状況とも言えます。

この章では、入り口からの歩き方として、はじめに試すべきサンプルやツールの紹介をします。

== Hello, Daydream

まずはHello Worldからです。

Google VR SDKはネイティブ（Java, C/C++）やUnreal Engineもサポートしていますが、Unityの情報が一番多く、試す際にはオススメのプラットフォームです。
本章では、とくに断りがなければUnityのバージョンは「2017.2.0f3」を、GVR SDKのバージョンは「v1.100.1」を利用しています。

基本的には以下のページの手順に従います。

 * Get started with Google VR in Unity on Android
 ** @<href>{https://developers.google.com/vr/unity/get-started}

 1. 新規3Dプロジェクトを作成し、「GoogleVRForUnity_1.100.1.unitypackage」をダウンロードしてインポート
 2. APIの自動アップグレード確認ダイアログが出るため、了承して実行
 3. 「GoogleVR＞Demos＞Scenes」配下の「GVRDemo」シーンを開く
 4. 「Build Settings」を開いて、「GVRDemo」シーンをビルド対象に追加、Platformを「Andorid」に「Switch Platform」を実行
 5. 「Player Settings」を開いて、以下の設定を変更
 6. 「Other Settings」より「Package Name」を適当な文字列に変更
 7. 同じく「Other Settings」より「Minimum API Level」を「Android 7.0 'Nougat' (API level 24)」に変更
 8. 「XR Settings」の「Virtual Reality Supported」をチェックして有効に、「Virtual Reality SDKs」の「+」ボタンを選択して、「Daydream」を追加
 9. 「Build and Run」を実行、apkの名前は適当に入力

//image[gvr-sdk-gvrdemo-01][GVRDemoサンプルシーン][scale=0.75]

うまくいくと、灰色の空間上に、赤色のキューブが浮かんでいるアプリが立ち上がります。
Daydreamコントローラを（ホーム長押しで）有効にして、ポインタをあててみましょう。
赤色のキューブが青緑に色に変化します（@<img>{gvr-sdk-gvrdemo-01}）。
キューブをポインタで示して、タッチパネルをクリックすると、部屋内のどこかにワープします。

== Instant Preview

前節で紹介したGVRDemoにはDaydream向けのステレオ表示とヘッドトラッキングの（自動的な）制御から、コントローラの接続状態のハンドリング、コントローラ操作での3Dオブジェクトに対するRay（光線）制御によるヒット判定とメニュー操作と、基本が詰まっており、根幹としてはこれがDaydreamの全てです。

さて、つづけて具体的なアプリを開発していきましょう、となった際に、毎回ビルドとAndroidデバイスへの転送、インストールを待って…というサイクルを繰り返すのは効率的ではありません。
できればUnityエディタ上で再生して、開発サイクルを回していきたいですよね。

=== Unityエディタ上での頭の振りやコントローラ操作のシミュレーション

まず、UnityエディタのGameウィンドウに対する操作で、頭を振ったり、Daydreamコントローラの操作がシミュレートされています。
GVRDemoのプレビュー再生中に、以下の操作を試して見てください。

 * Alt + マウス移動：頭の回転を操作
 * Ctrl + マウス移動：頭の傾きを操作
 * Shift + マウス移動：Daydreamコントローラの傾きを操作
 * Shift + マウス左クリック：Daydreamコントローラのタッチパッドのクリック
 * Shift + マウス中央クリック：DaydreamコントローラのHomeボタンのクリック（recenter扱い）
 * Shift + マウス右クリック：DayrdreamコントローラのAppボタンのクリック
 * Shift + Ctrl + マウス移動：Daydreamコントローラのタッチパッド上でのスワイプ操作

//image[gvr-sdk-editor-simulation][Unityエディタ上でのDaydreamコントローラのタッチパッドシミュレーションの様子][scale=0.75]

ひととおりの動作ができるようになっています。
少々操作は複雑ですが、タッチパッドのスワイプ操作も可能です（@<img>{gvr-sdk-editor-simulation}）。

=== ヘッドセットを被ってプレビューしたい

Unityエディタ上では平面でしかありませんので、ヘッドセットを被った上で立体で確認したいですし、首振りやコントローラ操作はもう少し直感的に試したいところです。
そこでInstant Previewの登場です。

 * Instant Preview
 ** @<href>{https://developers.google.com/vr/tools/instant-preview}

//image[gvr-sdk-instant-preview][Instant PreviewとController Emulatorセットでの動作の様子][scale=0.90]

Instant Previewは、専用のアプリをAndoridデバイス上で動作させ、Unityエディタと通信させてこれを実現するものです。
画像はUnityエディタからInstant Previewアプリへの映像ストリーミングで実現します。
また、逆方向でDaydreamコントローラの操作による入力も可能です。
コントローラの操作については前章で紹介したController EmulatorアプリによるDaydreamコントローラのエミュレートにも対応しています（@<img>{gvr-sdk-instant-preview}）。
USB・Wi-Fi経由いずれも使えます。
ただし、Wi-Fi経由については映像ストリーミングのための通信帯域の観点や、特定のマルチキャストアドレスとポートによる通信が可能なネットワークである必要があり、USB経由の方がお手軽です。

前節で動かしたGVRDemoシーンに、Instant Previewに必要なPrefabがすでに含まれています。
Daydream母艦となるAndroidデバイスをUSBで接続して、Unityエディタで再生すると、必要なアプリのインストールと起動は自動的に行われ、映像の再生がすぐに始まります。

コントローラについては、実デバイスであればHomeボタンの長押しを、Controller Emulatorであればアプリを起動してBluetoothの接続を待つだけです。

adb（Android Debug Bridge）コマンドまわりを使っているため、UnityエディタからAndroidアプリのビルドとインストール・実行が正常に動く環境であれば問題なく動作するはずです。
うまくいかない際には紹介したページ内に「Troubleshooting in Unity」という項目がありますのでそちらを参照ください。

== Daydream Elements

//image[daydream-elements-app-menu][Daydream Elements起動画面メニュー][scale=1.00]

 * Daydream Elements Overview
 ** @<href>{https://developers.google.com/vr/elements/overview}

Daydream ElementsはDaydreamのサンプル集です。
アプリはGoogle Playで公開されている他、ソースコードもGitHubで公開されています。

ものすごくよくできたサンプル集で、以下に特徴をあげます。

 * GVR SDKのライブラリ群の一つとして位置づけられ、多数のデモサンプルが含まれる
 * 多数のデモサンプルは1つのアプリにまとまっていて、そのメニューや階層構造と各デモ間の遷移も操作感が大変よい
 * 各デモは丁寧な説明看板と遊び心がたっぷり詰まったインタラクションのあるプレイアブルなものになっている
 * 統一感のあるUIでDaydreamのデザインガイドラインが直感的にわかるようになっている

//image[daydream-design-sketch][Daydreamデザインガイドライン資料（sketchファイル）の一部][scale=0.75]

Daydreamのデザインについては、ガイドラインがあります。
Sticker Sheetというページ@<fn>{daydream-design-guideline}から、sketchファイルが1つ（@<img>{daydream-design-sketch}）と、Google I/Oで解説したYouTube動画へのリンクが貼られています。

Daydreamのホームアプリはもちろん、Daydream Elementsアプリや後述するMedia App Templateアプリもこのガイドラインでデザイン統一されています。
一度目を通しておくとデザインガイドラインとその根拠がわかります。

//image[daydream-elements-02][Daydream Renderer（左）・Arm Models（中）・Constellation Menu（右）][scale=0.90]

光源数などに制限がある、モバイル向けに最適化された動的なライティングを行うDaydream Renderer、様々な移動やメニュー・インタラクションのデモ、傾きのみの3DoFながら腕の構造のエミュレーションによって擬似的に6DoFに近い動きを実現するArm Modelとそのパラメータを設定し、確認するデモなど、多数のデモが含まれています。
ぜひそれぞれのドキュメントを読みながら確認してみてください。

//footnote[daydream-design-guideline][Design | Sticker Sheet @<href>{https://developers.google.com/vr/design/sticker-sheet}]

== VR VideoとDaydream Media App Templateアプリ

=== GVR video plugin

Daydream Elementsと似た位置づけですが、GVR SDK for Unityには「GVR video plugin」という動画再生ライブラリが含まれます。

VR動画として必要な、「モノラル/Top-Bottomのステレオ/Left-Rightのステレオ」×「フラット/180度/360度」の3x3の9パターンの動画再生に対応しています@<fn>{codec-spec}。
ExoPlayerをベースにしており、シークやサムネイル取得も含め、ローカルファイルの再生のほか、HLSやDASHのようなadaptive streaming@<fn>{adaptive-streaming}にも対応しています。

//footnote[codec-spec][フォーマットやスペックについては「@<chapref>{daydream}」で述べた、CDDとDaydreamの要件の項を参照ください。]

//footnote[adaptive-streaming][直接の意味はネットワーク状態に応じて再生品質を制御するストリーミングのことです。ただし、ここでは「近年のいい感じのストリーミング技術」ぐらいの意味が近いと思われます。]

=== Daydream Media App Template

//image[daydream-media-app-template-01][Daydream Media App Templateアプリでの2D動画再生中画面][scale=0.75]

このGVR video pluginにも、Daydream Elementsと同様に、メディア再生アプリのテンプレートとなるひととおりの機能の揃ったサンプルアプリ（@<img>{daydream-media-app-template-01}）とunitypackage形式のリリースパッケージ、そしてもちろんソースコード一式がGitHubで公開されています。

 * Daydream Media App Template
 ** @<href>{https://developers.google.com/vr/unity/media-app-template}
 * GitHub: googlevr/media-app-template: Daydream Media App Template
 ** @<href>{https://github.com/googlevr/media-app-template}

//image[daydream-media-app-template-02][ファイラー表示（左）とVR動画のためのステレオ・投影設定メニュー（右）][scale=1.00]

特徴を以下に述べます。

 * メディアライブラリにアクセスするためのPermissionをユーザに確認するフロー実装に対応
 * ファイラーとしてフォルダ表示と移動、ファイルサムネイル表示とそれらの選択に対応（@<img>{daydream-media-app-template-02}-左）
 * 静止画・動画の再生に対応
 ** 静止画またはフラット動画は縦スワイプによる拡大縮小、ドラッグによる表示位置の移動に対応
 ** VR動画としてのフォーマット選択メニューでステレオのTop-Bottom/Left-Rightや180度/360度の切り替えにも対応（@<img>{daydream-media-app-template-02}-右）
 ** 動画のシークに対応、ポインタのオーバーレイによるシーク位置のサムネイルプレビューにも対応
 * Daydreamのデザイン・つくり観点でのガイドラインを満たしている

VR動画はドラッグによって水平方向の回転も可能です@<fn>{drag-pitch}。

ローカルにVR動画の資産がいくつかある方はぜひ試してみてください。
サンプルアプリとは思えないレベルで作り込まれているなと感じました。
ストリーミングサービスのバックエンドがあるなど、特定目的のDaydreamメディアアプリを開発したい際には、大変有力な手助けになると思われます。

//footnote[drag-pitch][縦方向（ピッチ）の回転にも対応しているとベストだったのですが、それぐらいは自分で改造すればいいってことですよね、はい。]

== 6DoFモーショントラッキングシステム NOLOを試す

=== NOLOとKickstarter

//image[nolo-site-photo][NOLO公式サイト][scale=0.90]

NOLO@<fn>{nolo-site}は6DoFのモーショントラッキングシステムです（@<img>{nolo-site-photo}）。
ベースステーション、ヘッドセットマーカー、2つのモーションコントローラからなるセットです。
モバイル形態で利用時には、完全にケーブルレスで、フロント方向限定ながら2つのコントローラを含むルームスケールでのポジショントラッキングを実現します。
PC経由で利用時にはケーブルが1本だけ伸びますが、RiftCat + VRidge@<fn>{riftcat-and-vridge}を利用することで、低遅延の映像ストリーミングにて、SteamVRのアプリをプレイすることができます。

2017年の1月末にKickstarter@<fn>{nolo-kickstarter}でのクラウドファンディングが開始され、NOLO一式のコースが$89〜$109とそれなりの低価格で設定されました。
CardboardやGear VR環境のスマートフォンは持っていても、HTC ViveやOculus RiftなどのPC VR環境を持っていないユーザにとって、NOLOは価格面においても期待された選択肢の一つでした。

ケーブルレスでポジショントラッキング付き、「6DoFのモバイルVR」としてはDaydream standaloneやOculusのSanta Cruzや、ARKit/AR Core + Daydreamが競合デバイスと考えられますが、NOLOはその先駆者と言えます。
NOLOのもう一つの形態であるPC経由については、HTC Viveのケーブルが新型で細くなったことや、Steam VR対応のWindows MRの登場もあって残念ながら今後はかなり厳しそうです。

//footnote[nolo-site][NOLO - Motion Tracking for VR @<href>{https://www.nolovr.com/}]
//footnote[riftcat-and-vridge][VRidge - Play PC VR on your Cardboard @<href>{https://riftcat.com/vridge}]

//footnote[nolo-kickstarter][NOLO: VR Motion Tracking for Mobile and SteamVR Play by Lisa Zhao — Kickstarter @<href>{https://www.kickstarter.com/projects/243372678/nolo-affordable-motion-tracking-for-mobile-and-ste}]

=== モバイルモードでアプリを試す

//image[nolo-android][モバイルモードでのNOLO一式][scale=1.00]

さて、そんなNOLOですが、backして届いたものを長らく放置していたのですが、いまさらになって試してみました。
ここからは試した内容についてお届けします。

NOLOの公式サイト、「Support」内に英語版の「Product Manual」が公開されています@<fn>{nolo-manual}。初期セットアップの「Pairing」と、今回は「Android Phone」（Cardboard相当と思われます）を選択します。

ベースステーションの電源を入れてペアリングモードにした後、コントローラ2つとヘッドセットマーカーの3ユニットをペアリングしていきます。
ここまでは操作もマニュアル通りで、LEDの表示も親切であり、とくにトラブルなくセットアップが終わりました。
NOLOのモバイルモードはAndroidのUSB Host機能を使っていますので、ヘッドセットマーカーとAndroidを付属のUSBケーブルで繋ぎます。
Gear VRのヘッドセットと同様の仕組みですが、NOLOにはGear VRのような統合管理を担当するコンパニオンアプリがないため、このあたりから操作難易度が上がってしんどくなってきます。

NOLO Tetris@<fn>{nolo-tetris}というアプリが公式サイトからダウンロードできる他、Google Playでも公開されているようなので試して見ましょう。

//image[nolo-tetris][ヘッドセットマーカー接続時の確認ダイアログ（左）とNOLO Tetrisのプレイ画面（右）][scale=1.00]

手順としては以下の通りです。
決して少なくない上に、とくにヘッドセットマーカーをUSBで接続時に表示されるダイアログのOKがタップしづらくてたまりません（@<img>{nolo-tetris}-左）。

 1. ベースステーションの電源を入れる
 2. コントローラの電源を入れる
 3. ヘッドセットマーカーをVRゴーグルにセットする
 4. スマートフォンとヘッドセットマーカーを専用のUSBケーブルで接続し、USB Host機能の確認ダイアログでOKをタップする
 5. スマートフォンをVRゴーグルにセットする
 6. トラッキングがうまくいっていなかったら2.あたりからやりなおし

空中に浮かんでいるブロックから好きなのを選んで盤面に近づけると、通常のテトリスのようにハマりこみます（@<img>{nolo-tetris}-右）。
ちゃんと横ラインを消すと消えるので確かにテトリスの模様です。

トラッキングがうまく行く勝率は3割ぐらいで、一度うまくいくとその後しばらくは安定します。
ただし、そもそもすべてがうまくいってる状態でもヘッドセットもコントローラもプルプルと震え@<fn>{nolo-world-shake}、数秒に1回程度、10cmから30cmほどスィーッと滑ります。
これは厳しい。

他のアプリも試して見ます。
もう一つの宇宙戦争っぽいアプリはコントローラが動かず、SDK for Android Javaのサンプルアプリはスクリーショット例のようにきちんとログは出てくれず、正常に動いていないように見えました。
Forumを探しているうちに見つけたNOLO GUNというアプリは動くには動いたのですが、銃をもったり弾をこめたりする操作性が悪すぎてとても辛かったです。

//footnote[nolo-manual][User Guide — NOLO - Motion Tracking for VR @<href>{https://www.nolovr.com/user-guide-en}]
//footnote[nolo-tetris][NoloTetris - Google Play @<href>{https://play.google.com/store/apps/details?id=com.lyrobotix.nolodaydream}]
//footnote[nolo-world-shake][ヘッドセットの位置認識がプルプル震えるとどうなるかというと、VR空間上で世界がプルプルと震えます。SaGa2の非常階段から最下層みたいな感じです。]

=== NOLO + Daydream

さて、そんなプルプルにもスィーッにもめげずに、Daydreamで動くか試してみました。
空中や水中で浮いてるようなケースに限定すればそれなりに楽しめる可能性がありますからね！
基本的にはGitHub上で公開されているNOLO-Unity-SDKの「Get Started」@<fn>{nolo-unity-get-started}の手順の通りです。
この際に、Daydreamコントローラは使わないため、前章で述べた「VR Entry Flow」の無効化設定はONにしておくことをオススメします。

Unityのバージョンは2017.2.0f3で確認しています。
NoloVR_SDK_1.1.7_20171017.unitypackageをダウンロードしてインポートします。

//image[nolo-unity-01][SDK内Exampleフォルダ配下のTestサンプルシーンを選択][scale=0.6]

SDK内、Exapmpleフォルダ配下にはいくつかのサンプルシーンが含まれています。
ひとまずSDKとしてコントローラやヘッドセットマーカーの空間上の座標や向き、ボタンの状態などの情報が表示される、「NoloVR＞Example＞General＞Test」シーン（@<img>{nolo-unity-01}）を試してみます。

//image[nolo-unity-03][Testシーンの動作画面][scale=1.00]

前述のNOLO Tetrisと同様に、プルプル揺れたりスイーッと水平方向に滑る現象は（残念ながら）とくに変わりはありませんでしたが、各ユニットの座標・傾き、ボタンの状態はきちんととれていることが分かりました（@<img>{nolo-unity-03}）。
首振り制御の競合などが懸念されたDaydreamとしての動作もとく問題ないようです。
APIの動作が素直だと何かを作ってみようという気になりますね。

そんなわけで将来の猶予はあまりありませんが、可能性は感じました。
決して一般ユーザにはオススメはできませんが、機会があればちょっとだけ試す分には面白いデバイスだと思います@<fn>{nolo-try}。

//footnote[nolo-unity-sdk][NOLOVR/NOLO-Unity-SDK: NOLO Unity SDK @<href>{https://github.com/NOLOVR/NOLO-Unity-SDK}]
//footnote[nolo-unity-get-started][NOLO-Unity-SDK/GetStarted.md @<href>{https://github.com/NOLOVR/NOLO-Unity-SDK/blob/master/Docs/en_us/GetStarted.md}]
//footnote[nolo-try][相性問題が多くセットアップ難易度が高すぎるとか、不安定ですぐ落ちるとか、ハック口がまったく開いていないとか、そういうデバイスではないということです。ガジェットのクラウドファンディング結果としては満足しています。]

