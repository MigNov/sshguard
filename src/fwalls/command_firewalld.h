/*
 * Copyright (c) 2014 Michal Novotny <mignov@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * SSHGuard. See http://www.sshguard.net
 */

#ifndef COMMAND_H
#define COMMAND_H

/* sample command.h content for netfilter/iptables */


#include "../config.h"

/* for initializing the firewall (+ make sure we have sufficient credentials) */
#define COMMAND_INIT        FIREWALLD_PATH "/firewall-cmd --direct --get-rules ipv4 filter INPUT"

/* for finalizing the firewall */
#define COMMAND_FIN         ""

/* for blocking an IP */
/* the command will have the following variables in its environment:
 *  $SSHG_ADDR      the address to operate (e.g. 192.168.0.12)
 *  $SSHG_ADDRKIND  the code of the address type [see sshguard_addresskind.h] (e.g. 4)
 *  $SSHG_SERVICE   the code of the service attacked [see sshguard_services.h] (e.g. 10)
 */
//#define COMMAND_BLOCK       FIREWALLD_PATH "/firewall-cmd --zone=public --add-source=$SSHG_ADDR"
#define COMMAND_BLOCK       FIREWALLD_PATH "/firewall-cmd --direct --add-rule ipv$SSHG_ADDRKIND filter INPUT 0 -s \"$SSHG_ADDR\" -j DROP"

/* iptables does not support blocking multiple addresses in one call.
 * COMMAND_BLOCK_LIST can not be provided here, a sequence of calls to
 * COMMAND_BLOCK will be automatically used instead */

/* for releasing a blocked IP */
/* the command will have the following variables in its environment:
 *  $SSHG_ADDR      the address to operate (e.g. 192.168.0.12)
 *  $SSHG_ADDRKIND  the code of the address type [see sshguard_addresskind.h] (e.g. 4)
 *  $SSHG_SERVICE   the code of the service attacked [see sshguard_services.h] (e.g. 10)
 */
#define COMMAND_RELEASE     FIREWALLD_PATH "/firewall-cmd --direct --remove-rule ipv$SSHG_ADDRKIND filter INPUT 0 -s \"$SSHG_ADDR\" -j DROP"

/* for releasing all blocked IPs at once (blocks flush) */
#define COMMAND_FLUSH       "/bin/systemctl restart firewalld.service"

#endif

