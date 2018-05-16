#@# VRコンテンツのつくりかた2 技術書典3
#@# （）かっこは全角統一する。
#@# ユーザ入力は""ダブルクォーテーション、メニュー表示文字列は「」かぎかっこにでくくる。

= Hello, Mirage Solo

== 本章について

本章は主に発売前にお借りしたMirage Soloにて、ビルド番号@<code>{OVR1.180406.005}のファームウェアでの確認事項を掲載しています。
今後のアップデートにより記載内容について変更される可能性があることをご了承ください。

== Mirage Soloとは

//image[miragesolo-01][Mirage Solo - Lenovo][scale=0.75]

Mirage Solo@<fn>{miragesolo-lenovo}は2018年5月、Lenovoから発売となった単独で動作する一体型のVRヘッドセットである、Daydream standalone機です。
Daydream standaloneそのものについては「@<chapref>{daydream}」ですでに説明済みですので、そちらを参照願います。

=== 製品仕様へのコメント

製品仕様@<fn>{miragesolo-lenovo}について、以下に抜粋してコメントしておきます。

 * Qualcomm® APQ8098 オクタコア プロセッサー （最大2.45GHz）：Qualcomm Snapdragon835 VR Platformベースです。
 * Daydream 2.0：AndroidベースでDaydream 2.0 Euphratesアップデートが全て含まれます。セパレート側のDaydreamでも概ね対応されていますが、ChromeCastなどを用いた専用単眼画面のスクリーンキャスト、ホーム画面とは別の通知確認画面、左右アーム設定のクイック変更などが含まれます。
 ** コントローラ操作による静止画・動画スクリーンショットは、現状開発者向けオプションで有効にする必要があります。全ユーザへの解放を計画しているとのことです。
 ** YouTubeアプリの「皆で見てる方向を共有」はアプリのアップデートで対応されました。
 ** ChromeアプリのWebVRを含むVRフル対応は2018.05現在、準備中とのこと。
 * 5.5型IPSパネル（2560 x 1440ドット）：液晶です。かなり綺麗です。「非球面フレネルレンズ、110°FOV」とセットで、現行機ではトップクラスの画質です。
 * WorldSense対応デュアル・モーション・トラッキング・カメラ：Androidの標準カメラAPIでは使えません。モノクロで、とくに今後APIが解放される予定もないとのことです。
 * Android N Proオーディオ：Android公式ドキュメントの「オーディオ レイテンシ@<fn>{android-audio-latency}」の@<code>{android.hardware.audio.pro}の項のことを指していると思われます。

//footnote[miragesolo-lenovo][@<href>{https://www3.lenovo.com/jp/ja/vr-smartdevices/augmented-reality/lenovo-mirage-solo/Mirage-Solo/p/ZZIRZRHVR01}]
//footnote[miragesolo-spec][Lenovo Mirage Solo with Daydream 製品仕様書 ZA3C0011JP | レノボジャパン  @<href>{https://www3.lenovo.com/jp/ja/static/catalog/vr-2018_mirage_solo_rt_0424}]
//footnote[android-audio-latency][オーディオ レイテンシ  |  Android NDK  |  Android Developers @<href>{https://developer.android.com/ndk/guides/audio/audio-latency}]

== セットアップ

それでは主に開発者向け観点でのセットアップを実行していきましょう。

=== 初回セットアップ

それでは、電源を入れてセットアップを行いましょう。

起動後、まずDaydreamコントローラの認識シーケンスが始まります。
画面の指示にしたがって、コントローラのDaydreamボタン（一番下のボタン）やタッチパッドの領域を操作してください。

「Hi, there」画面にて言語を選択します。インターネットに繋がったWi-Fi環境に接続の上、Googleアカウントのセットアップを行います。
キーボードは選択した言語に依存しますので、Wi-Fiパスワードやメールアドレスを入力する際には、地球儀の用なマークを選択して、英語（半角英数）モードに切り替えてください。

その後、チュートリアルが始まります。
チュートリアルも空間音響とポジショントラッキングがよく効いた素敵なデモになっていますので、できればヘッドホンかイヤホンを接続の上実施してください。

=== 開発者向けオプションとadbの有効化

何はともあれ、開発者向けオプションを有効にして、adbを使えるようにしましょう。
以下に、開発者向けオプションとadbの有効化手順を示します。

//image[miragesolo-dashboard][Dashboard画面][scale=0.75]

 * Daydreamボタンを1回押すと、Dashboardが表示されます（@<img>{miragesolo-dashboard}）。
 ** Dashboardでは、よく使うアプリの起動や通知の確認、各種設定が行えます。
 * 右上のギアマークの「設定」を選択し、さらに「全ての設定」を選択すると、2Dビューで設定画面が表示されます。
 * 「設定」＞「システム」＞「端末情報」から、「ビルド番号」を7回タップします。メニュー構成は違いますが、お馴染みの操作です。「これでデベロッパーになりました！」というToastが表示されれば成功です。
 * ひとつメニュー階層を戻って、「開発者向けオプション」から「USBデバッグ」を有効にします。
 * Android SDKがセットアップ済みの母艦PCとUSBケーブルで接続し、@<code>{adb devices}コマンドなどで接続を試みると、お馴染みのフィンガープリント確認ダイアログが出ますので許可してください。確認が終了すると、adbが有効になります。

==== 開発者向けオプションの罠

設定画面のような2Dビューを特殊な方法で実現しているのか、画面オーバレイ表示を行う開発者向けオプションが一部うまく動きません。
ポインタの座標情報を表示する「ポインタ表示」設定はONにするとその後正常に画面が描画されなくなり、@<kw>{factory reset必須になりますのでご注意ください。}

=== Daydreamのデベロッパー向け設定

//image[miragesolo-developer-settings-01][Daydreamのデベロッパー向け設定][scale=0.75]

「@<chapref>{daydream-setup}」の「デベロッパー向け設定とVR Entry Flow」でも紹介した、Daydream向けデベロッパー向け設定はMirage Soloでも有効です。
「設定」＞「Daydream」＞「VRの設定」＞「デベロッパー向けの設定」（表示されていなければ「ビルドバージョン」を7回タップ）にて開くことができます。

==== デベロッパー向け設定の紹介

 一部抜粋して説明します。
 チェックしても特に効果がないように見えるオプションもあります。

  * 「Enable performance monitoring」＋「Enable performance heads-up display」：VRアプリ中にパーフォーマンスモニタをHUDの形でオーバレイ表示します。ただし、非一体型と違ってスクリーンショットに写らないため、確認にはひと手間かかります。
  * 「Force 6DoF in Apps」：非6DoF対応アプリにて、強制的に6DoFヘッドトラッキングを可能にします。ただし、全天球動画など、カメラから特定距離に張り付いたオブジェクトに近づけるわけではありませんので、過度の期待は禁物です。
  * 「Enable safety graphics」：デフォルトで有効になっていますが、これを外すことにより「カメラリセット位置から一定距離離れると注意事項とともにブラックアウトする」安全のためのガードを外すことができます。これをoffにすることを前提としたアプリはGoogle Playでは配布できません。展示向けなど、安全に配慮できるケースにおいては、WorldSenseのポジトラの性能を最大限活かすことができます。
  *  「Force undistored rendering」：動画キャプチャやChromecastなどへのスクリーンキャスト時に、強制的に樽型歪みを解除します。あまり詳細が分かっていませんが、静止画・スクリーンショット絡みの設定を有効にする際に、あわせて有効にしておくのが良さそうです。
  * 「Enable VR screen recording via chords」：有効にすると、コントローラの「Daydreamボタン（一番下のボタン）＋ボリュームダウンの長押し」で静止画スクショが、「Daydreamボタン＋ボリュームアップボタンの長押し」で動画の撮影開始/撮影停止ができるようになります。
  ** 「You will need to grant permission to Google VR Services」という、Google VRサービスへの権限設定の操作がわかりづらいのですが、次のようにMirage Solo内で操作します。
  ** @<kw>{Dashboardの「すべての設定」より、「アプリと通知」＞「N個のアプリをすべて表示」＞右上の「：」より「システムを表示」＞「Google VR サービス」＞「権限」＞ストレージの権限をON}
  * 「Enable VR screen recording via ADB」：有効にすると、adbコマンドから静止画・動画キャプチャができるようになります。コマンドが少々複雑なため、aliasやmacroを組むのをオススメします。
  ** 詳細はメニューにある通り、コマンドからヘルプを表示することができます。
  ** @<code>{adb shell am startservice -n com.google.vr.vrcore/.capture.record.RecorderService --es command HELP}

==== adb経由の静止画・動画キャプチャとalias

adb経由の静止画・動画キャプチャですが、コマンドが少々複雑なこと、@<kw>{MTPが（2018.05現在）動かない}ため、ファイル名指定と、@<code>{adb pull}を組み合わせたaliasやmacroを組むことをオススメします。
以下、コマンド説明とalias例です。

 * mirage-image：静止画キャプチャを行ったあと、メディアファイルをMirage Soloから取得します。
 ** @<code>{alias mirage-image='now=$(date "+%Y%m%d-%H%M%S");adb shell am startservice -n com.google.vr.vrcore/.capture.record.RecorderService --es command IMAGE --es path /sdcard/Pictures/${now}.jpg;sleep 1;adb pull /sdcard/Pictures/${now}.jpg .'}
 * mirage-start：動画キャプチャを開始します。
 ** @<code>{alias mirage-start='now=$(date "+%Y%m%d-%H%M%S");adb shell am startservice -n com.google.vr.vrcore/.capture.record.RecorderService --es command START --es path /sdcard/Movies/${now}.mp4;'}
 * mirage-stop：mirage-startとセットで使用します。動画キャプチャを停止し、メディアファイルをMirage Soloから取得します。
 ** @<code>{alias mirage-stop='adb shell am startservice -n com.google.vr.vrcore/.capture.record.RecorderService --es command STOP;sleep 1;db pull /sdcard/Movies/${now}.mp4 .'}
 * mirage-photo：写真アプリを2Dビューで起動します。
 ** @<code>{alias mirage-photo='adb shell am start -n com.google.android.apps.photos/.home.HomeActivity'}

=== fastbootとfactory reset

//image[fastboot-recovery][fastbootとrecovery mode][scale=0.8]

他のAndroidデバイスと同様、fastbootメニューからのfactory resetが可能です。
操作不能に陥った際には実施しましょう。

 * 電源OFFの状態で、音量（-）ボタンを押したまま、電源ボタンを2秒ほど押して話すと、fastbootモードで起動します（@<img>{fastboot-recovery}-左）。
 * fastbootモードにて、音量ボタンにて「RECOVERY MODE」を選択し、電源ボタンで決定操作をします。
 * ドロイド君に赤い警告マークが出て「No Command」と表示された画面で、電源ボタンを押しながら、音量（+）ボタンを押すと、RECOVERY MODEのメニューが表示されます（@<img>{fastboot-recovery}-右）。
 * 同じく音量ボタンと電源ボタンにて、「Wipe data/factory reset」を選択すると、factory resetが実施されます。「Wipe data」の通り、全てのデータは初期化されます。

=== その他便利な話・Intent芸

==== Google Playのリモートインストール＋adb shell am startで直接起動

ブラウザでGoogle Playのサイトを開き、リモートインストールすることが可能です。インストール後は@<code>{adb shell pm dump <package名>}にて対象のActivityを特定し、@<code>{adb shell am start}で直接起動しましょう。
アプリのpakcage名はGoogle PlayサイトのURLから確認できます。

いくつか起動コマンド例を載せておきます。

 * Slack：@<code>{adb shell am start -n com.Slack/.ui.HomeActivity}
 * Twitter：@<code>{adb shell am start -n com.twitter.android/.StartActivity}
 * Google Photo（プリイン）：@<code>{adb shell am start -n com.google.android.apps.photos/.home.HomeActivity}

また、手順が複雑ですが、インターネットに接続されている状態であればメニュー操作でも起動することが可能です。
Dashboardの「すべての設定」より、「アプリと通知」＞「N個のアプリをすべて表示」＞起動したいアプリを選択＞「アプリの詳細」でGoogle Playの該当ページを開く＞「開く」を選択してアプリを起動する。

Daydreamに対応した非VRアプリも含めて起動するランチャーを作ってしまえば解決するかな、とも思っています。

==== 直接起動するだけのDaydreamアプリを作る

Intentもアプリ詳細を辿る操作も不便なので、「Daydreamのルールにのっとりホームやライブラリにアイコンが表示される」かつ「Intentで特定パッケージのアプリを起動する」アプリを作ればいいわけです。

//image[twlauncher-01][TwLauncher for Daydream standalone][scale=0.6]

作りました。

ひとまず、Twitterを直接呼ぶアプリを試しに作ってみました。Playで公開している@<fn>{twlauncher-twitter}の他、GitHubにソースコード一式@<fn>{twlauncher-github}を置いています。

ほぼコードを書いていないこのアプリがそれなりに便利だったので、既存のランチャーアプリを起動するショートカットアプリを作ればすべてが解決するのでは、と考えました。
AtomicAdd Teamの「小型デスクトップ（ランチャー）@<fn>{tinylauncher}」というアプリが便利だという情報を見つけましたので、これ向けにパッケージ名を変更したものを用意してみたところ、よさそうです@<fn>{twlauncher-tinylauncher-branch}。
ただし、いわゆる「ホームアプリ」を複数インストールするとややこしいことになりますのでそのあたりは知ってる人だけお試しください。

//footnote[twlauncher-github][@<href>{https://github.com/youten/TwLauncher}]
//footnote[twlauncher-twitter][TwLauncher for Daydream standalone @<href>{https://play.google.com/store/apps/details?id=tw.youten.redo.tw}]
//footnote[tinylauncher][@<href>{https://play.google.com/store/apps/details?id=com.atomicadd.tinylauncher}]
//footnote[twlauncher-tinylauncher-branch][@<href>{https://github.com/youten/TwLauncher/blob/28e435de7c1f483691da5f8f73e0def648343c9a/tinylauncher.apk} 使ってみた動画はこちらのツイートを参照@<href>{https://twitter.com/youten_redo/status/995362623381159936}]

==== Bluetoothヘッドホンなどを使う

Bluetooth設定が塞がれていますが、 Bluetooth設定をIntent（@<code>{adb shell am start -a android.intent.action.MAIN -n  com.android.settings/.bluetooth.BluetoothSettings}）にて直接開くと使うことができます。
ただし、これについてはコントローラのBluetooth通信帯域確保のために意図的に塞いでいるとのことです。
コントローラが不安定になる可能性があります。

=== いろいろ動かない話

最後に、いろいろ動かない話を挙げておきます。今後のアップデートで改善されることを期待しています。

 * Instant Previewが真っ暗
 ** 近接センサを抑えると、コントローラ中継エミュレーションだけは動いているのを確認できます。こちらは修正予定とのことです。
 * Vysorが動かない
 * MTPが動かない
 ** 正直びっくりしました。どうもMirage Solo内で一般ユーザがスクリーンショットなどを扱うことを考慮していないようです。 前述したコントローラによるスクリーンショットを有効にした上で、@<code>{adb pull}または「2D ViewのGoogle Photoアプリを起動して自動バックアップフォルダを指定」することにより、インターネット経由で取得することができます。
 * VR対応Chromeがない
 ** Chrome VR（WebVRとVRモード正式対応のバージョン68と思われます）で正式対応予定とのことです。
 ** Chrome Dev@<fn>{chrome-dev}やChrome Canary@<fn>{chrome-canary}という開発版のAndroid向けChromeなどがVR向けモードを試験的に導入しています。これをinstallして、@<code>{chrome://flags}というURL入力から開く設定画面で、WebVRを有効にするとそれなりに動作します。「それなり」というのは、正式版ではないChromeではもともと機能が制限されていることと、マイク入力からの音声検索やタブ表示・切り替えなどが現状、正常に動作しません。
 ** 2D ViewのChromeは動作します。Chrome betaやfirefoxなどの別ブラウザアプリを入れることもできます。
 ** WebViewやChrome Custom Tabsは動作しましたが、筆者の確認手順ではカスタムURL schemeによるActivityフックが動かない（OAuth認証シーケンスが非一体型のDaydreamと同じ実装では動作しません！）のを確認しています。Intentによるアプリ連携・分業がAndroidの最高のメリットなため、このあたりは早急に修正されてほしいなと思っています。

//footnote[chrome-dev][@<href>{https://play.google.com/store/apps/details?id=com.chrome.dev} ]
//footnote[chrome-canary][@<href>{https://play.google.com/store/apps/details?id=com.chrome.canary}]
