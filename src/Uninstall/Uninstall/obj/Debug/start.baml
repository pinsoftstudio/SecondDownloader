   M S B A M L   `   `   `  ����@  <setup, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:setupsetup  5          setup.start   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      %localclr-namespace:setup     5        N� Title$  SecondDownloader��5       N� WindowTitle$ 安装SecondDownloader��6     � 	Resources 5
       �� 
TargetType   	submitbtn �� Property �� Value �� 
TargetType �� CornerRadius �� Triggers	 :� RoutedEvent
 �� TargetProperty	 �� To g� Duration g� FillBehavior W� From	 W� To g� AutoReverse  btn��%Y  &	        &	 %    �� 5   
   " ��6   .�5      ��  � ��
 �����6+   �� 5       � �� �#2983cc6+   �� 5       �@�Cursor$
 Hand��6'   �� 5       � �� 5      �� 5      " ��6&   .R�5      �� #��z��6!   $ 6��6K   ._�5      �� $��Center=�6/   $��Center=�6L   5      5      5       5      :� 5      $	 Button.MouseEnter��6   [�5      �� 5      .��5      �� .��5   "   �� $1
 +(Button.Background).(SolidColorBrush.Color)�61   $ #4f9dddX�5   -   $ 0:0:0.1D�6:   $ HoldEnd=�6M   6f   5#      5$      5&      :� 5'      $	 Button.MouseLeave��6   [�5(      �� 5)      .��5*      �� .��5+   "   �� $1
 +(Button.Background).(SolidColorBrush.Color)�61   $ #2983ccX�5,   -   $ 0:0:0.1D�6:   6O   5.      5/      51      :� 52      $	 Button.Click��6   [�53      �� 54      .��55      �� .��56   "   W� $
 (Button.Opacity)�57      $ 1X�58      $	 0.8X�6   $ 0:0:0.2D�6!    . 64   59      5:      5<      5>      �� 5?   
   " ��6   .�5@      ��  � �� �#0006+   �� 5A       � �� �#ddd6+   �� 5B       �@�Cursor$
 Hand��6'   �� 5C       � �� 5D      �� 5E      " ��6&   .R�5F      �� #��z��6!   $ 6��6K   ._�5G      �� $��Center=�6/   $��Center=�6L   5H      5I      5K       5L      :� 5M      $	 Button.MouseEnter��6   [�5N      �� 5O      .��5P      �� .��5Q   "   �� $1
 +(Button.Background).(SolidColorBrush.Color)�61   $ #e7e7e7X�5R   -   $ 0:0:0.1D�6:   $ HoldEnd=�6M   6f   5W      5X      5Z      :� 5[      $	 Button.MouseLeave��6   [�5\      �� 5]      .��5^      �� .��5_   "   �� $1
 +(Button.Background).(SolidColorBrush.Color)�61   $
 #dddX�5`   -   $ 0:0:0.1D�67   6L   5b      5c      5e      :� 5f      $	 Button.Click��6   [�5g      �� 5h      .��5i      �� .��5j   "   W� $
 (Button.Opacity)�5k      $ 1X�5l      $	 0.7X�6   $ 0:0:0.2D�6!    . 64   5m      5n      5p      5r      5s       J� Effect 5t      3  -System.Windows.Media.Effects.DropShadowEffect  5u   
   .��5w      � 
�������.+�5z   
   �� $
��Left=�6   $	��111��6+   $��Center=�68   $	��115��6S   $��	/logo.png��6_   $��	55,0,0,40q�6r    J� OpacityMask 5{      �� 5|       �� ImageSource$ 	/logo.png��6    j� TileMode$
 None=�65    j� Stretch$ Uniform=�6E   5~      �� 5   
   $��SecondDownloader��6   $
��Left=�6+   $��
186,0,0,80q�6F   $��Center=�6Z   $��Microsoft YaHei UI)�6u   $��25(�6�   �� 5�   
   $!��强大的多线程下载器��6   $
��Left=�6$   $��
186,0,0,15q�6?   $��Center=�6S   $��Microsoft YaHei UI)�6n   $��14(�6�   �� 5�   
   $ ��Developed by PinsoftStudio��6   $
��Left=�65   $��
186,30,0,0q�6P   $��Center=�6d   $��Cascadia Code)�6   �� 5�   
   -   5        $��卸载��5�      #��[  6   $��Microsoft YaHei UI)�6A   $��15(�6a   $��	0,0,10,10q�6o   $��60��6�   $��35��6�   $��Right=�6�   $��Bottom=�6�    �� 	ClickMode$ Press=�6�   5�      �� 5�   
   -   5        $��取消��5�      #��[ 6   $��Microsoft YaHei UI)�6;   $��15(�6[   $��	0,0,78,10q�6i   $��60��6|   $��35��6�   $��Right=�6�   $��Bottom=�6�   $ Press=�6�   5�      5�      5�      