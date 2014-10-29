Name:		sshguard
Version:	1.5
Release:	1
License:	GPLv2+
Summary:	Protect hosts from brute force attacks against ssh
Url:		http://www.sshguard.net
Group:		Productivity/Networking/Security
Source0:	http://downloads.sourceforge.net/sshguard/%{name}-%{version}.tar.bz2
Source1:	sshguard.init
Source2:	sysconfig.sshguard
Requires:	iptables
Requires:	openssh
BuildRoot:	%{_tmppath}/%{name}-%{version}-build

%description
Sshguard protects networked hosts from brute force attacks
against ssh servers. It detects such attacks and blocks the
attacker's address with a firewall rule.

%prep
%setup -q

%build
%configure \
  --with-firewall=custom \
  --with-custom=%{_sbindir}/sshguard-custom-script
make %{_smp_mflags}

%install
%makeinstall
mkdir -p %{buildroot}/%{_sbindir}
mkdir -p %{buildroot}/etc/sshguard
mkdir -p %{buildroot}%{_sysconfdir}/init.d
cp examples/sshguard-custom-firewalld %{buildroot}/%{_sbindir}/sshguard-custom-script
install -D -m 644 %{SOURCE2} %{buildroot}/etc/sshguard/whitelist
install -D -m 744 %{SOURCE1} %{buildroot}%{_sysconfdir}/init.d/sshguard

%post
chkconfig sshguard on > /dev/null 2>&1

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc Changes README.md examples/ scripts/
%{_sbindir}/sshguard
%config %{_sysconfdir}/init.d/sshguard
%doc %{_mandir}/man8/%{name}*
%{_sbindir}/sshguard-custom-script
/etc/sshguard/whitelist

%changelog
* Wed Oct 29 2014 Michal Novotny <mignov@gmail.com> 1.5-1
- Add 2 new backends: firewalld and custom handler

* Wed Oct 29 2014 Michal Novotny <mignov@gmail.com> 1.5
- Initial release (v1.5)

