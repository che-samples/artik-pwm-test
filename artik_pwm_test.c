#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <artik_module.h>
#include <artik_platform.h>
static artik_pwm_config config = {
    ARTIK_A5_PWMIO_XPWMIO1,
    "pwm",
    400000,
    200000,
    ARTIK_PWM_POLR_NORMAL
};
artik_error pwm_test_frequency(int platid)
{
    artik_pwm_handle handle;
    artik_error ret = S_OK;
    artik_pwm_module* pwm = (artik_pwm_module*)artik_get_api_module("pwm");
    if(platid == ARTIK5)
        config.pin_num = ARTIK_A5_PWMIO_XPWMIO1;
    else
        config.pin_num = ARTIK_A10_PWMIO_XPWMIO1;
    fprintf(stdout, "TEST: %s\n", __func__);
    ret = pwm->request(&handle, &config);
    if (ret != S_OK) {
        fprintf(stderr, "TEST: %s - Failed to request PWM (err=%d)\n", __func__, ret);
        return ret;
    }
    /* Wait for X seconds */
    usleep(3 * 1000 * 1000);
    pwm->release(handle);
    fprintf(stdout, "TEST: %s suceeded\n", __func__);
    return ret;
}
int main()
{
    artik_error ret = S_OK;
    int platid = artik_get_platform();
    if((platid == ARTIK5) || (platid == ARTIK10)) {
        ret = pwm_test_frequency(platid);
    }
    return (ret == S_OK) ? 0 : -1;
}