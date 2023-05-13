object FormMap: TFormMap
  Left = 227
  Top = 161
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Mapa nieba'
  ClientHeight = 406
  ClientWidth = 678
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  ShowHint = True
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 673
    Height = 305
    Cursor = crCross
    OnMouseMove = Image1MouseMove
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 384
    Width = 678
    Height = 22
    Panels = <
      item
        Text = 'Pozycja Myszy'
        Width = 50
      end>
    SimplePanel = False
  end
end
